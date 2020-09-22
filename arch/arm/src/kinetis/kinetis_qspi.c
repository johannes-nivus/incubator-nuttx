/****************************************************************************************************
 * arch/arm/src/kinetis/kinetis_qspi.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <arch/board/board.h>

#include <nuttx/arch.h>
#include <nuttx/wdog.h>
#include <nuttx/clock.h>
#include <nuttx/kmalloc.h>
#include <nuttx/semaphore.h>

#include "arm_internal.h"
#include "arm_arch.h"
#include "barriers.h"

#include "hardware/kinetis_memorymap.h"
#include "hardware/kinetis_qspi.h"
#include "kinetis_qspi.h"

#ifdef CONFIG_KINETIS_QSPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/


/* Clocking *****************************************************************/

/* The QSPI Baud rate clock is generated by dividing the peripheral clock by
 * a value between 1 and 255
 */

#define SAM_QSPI_CLOCK    BOARD_MCK_FREQUENCY  /* Frequency of the main clock */

/* DMA timeout.  The value is not critical; we just don't want the system to
 * hang in the event that a DMA does not finish.  This is set to
 */

#define DMA_TIMEOUT_MS    (800)
#define DMA_TIMEOUT_TICKS MSEC2TICK(DMA_TIMEOUT_MS)

/* QSPI memory synchronization */

#define MEMORY_SYNC()     do { ARM_DSB(); ARM_ISB(); } while (0)

/* The KINETIS QSPI driver insists that transfers be performed in multiples
 * of 32-bits.  The alignment requirement only applies to RX DMA data.
 */

#define ALIGN_SHIFT       2
#define ALIGN_MASK        3
#define ALIGN_UP(n)       (((n)+ALIGN_MASK) & ~ALIGN_MASK)
#define IS_ALIGNED(n)     (((uint32_t)(n) & ALIGN_MASK) == 0)

/* Debug ********************************************************************/

/* Check if QSPI debug is enabled */

#ifndef CONFIG_DEBUG_DMA
#  undef CONFIG_KINETIS_QSPI_DMADEBUG
#endif

#define DMA_INITIAL      0
#define DMA_AFTER_SETUP  1
#define DMA_AFTER_START  2
#define DMA_CALLBACK     3
#define DMA_TIMEOUT      3
#define DMA_END_TRANSFER 4
#define DMA_NSAMPLES     5

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* The state of the QSPI controller.
 *
 * NOTE: Currently the KINETIS supports only a single QSPI peripheral.  Logic
 * here is designed to support multiple QSPI peripherals.
 */

struct kinetis_qspidev_s
{
  struct kqspi_dev_s qspi;      /* Externally visible part of the QSPI interface */
  uint32_t base;               /* QSPI controller register base address */
  uint32_t frequency;          /* Requested clock frequency */
  uint32_t actual;             /* Actual clock frequency */
  uint8_t intf;                /* QSPI controller number (0) */
  bool initialized;            /* TRUE: Controller has been initialized */
  sem_t exclsem;               /* Assures mutually exclusive access to QSPI */

#ifdef CONFIG_KINETIS_QSPI_DMA
  bool candma;                 /* DMA is supported */
  uint8_t rxintf;              /* RX hardware interface number */
  uint8_t txintf;              /* TX hardware interface number */
  sem_t dmawait;               /* Used to wait for DMA completion */
  struct wdog_s dmadog;        /* Watchdog that handles DMA timeouts */
  int result;                  /* DMA result */
  DMA_HANDLE dmach;            /* QSPI DMA handle */
#endif

  /* Debug stuff */

#ifdef CONFIG_KINETIS_QSPI_DMADEBUG
  struct kinetis_dmaregs_s dmaregs[DMA_NSAMPLES];
#endif

#ifdef CONFIG_KINETIS_QSPI_REGDEBUG
  bool     wrlast;             /* Last was a write */
  uint32_t addresslast;        /* Last address */
  uint32_t valuelast;          /* Last value */
  int      ntimes;             /* Number of times */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Helpers */

#ifdef CONFIG_KINETIS_QSPI_REGDEBUG
static bool     qspi_checkreg(struct kinetis_qspidev_s *priv, bool wr,
                  uint32_t value, uint32_t address);
#else
# define        qspi_checkreg(priv,wr,value,address) (false)
#endif

static inline uint32_t qspi_getreg(struct kinetis_qspidev_s *priv,
                  unsigned int offset);
static inline void qspi_putreg(struct kinetis_qspidev_s *priv, uint32_t value,
                  unsigned int offset);

#ifdef CONFIG_DEBUG_SPI_INFO
static void     qspi_dumpregs(struct kinetis_qspidev_s *priv, const char *msg);
#else
# define        qspi_dumpregs(priv,msg)
#endif

/* DMA support */

#ifdef CONFIG_KINETIS_QSPI_DMA
#ifdef CONFIG_KINETIS_QSPI_DMADEBUG
#  define qspi_dma_sample(s,i) kinetis_dmasample((s)->dmach, &(s)->dmaregs[i])
static void     qspi_dma_sampleinit(struct kinetis_qspidev_s *priv);
static void     qspi_dma_sampledone(struct kinetis_qspidev_s *priv);

#else
#  define qspi_dma_sample(s,i)
#  define qspi_dma_sampleinit(s)
#  define qspi_dma_sampledone(s)

#endif

static void     qspi_dma_callback(DMA_HANDLE handle, void *arg, int result);
static inline uintptr_t qspi_regaddr(struct kinetis_qspidev_s *priv,
                  unsigned int offset);
#endif

static void     qspi_memcpy(uint8_t *dest, const uint8_t *src,
                  size_t buflen);

/* QSPI methods */

static int      qspi_lock(FAR struct kqspi_dev_s *dev, bool lock);
static uint32_t qspi_setfrequency(FAR struct kqspi_dev_s *dev,
                                  uint32_t frequency);
static FAR void *qspi_alloc(FAR struct kqspi_dev_s *dev, size_t buflen);
static void     qspi_free(FAR struct kqspi_dev_s *dev, FAR void *buffer);
static int      qspi_command(FAR struct kqspi_dev_s *dev,
                  FAR struct kqspi_cmdinfo_s *cmdinfo);
static void     qspi_setconfig(FAR struct kqspi_dev_s *dev,
                  FAR struct kqspi_config_s *conf);
static void     qspi_setlut(FAR struct kqspi_dev_s *dev, FAR uint32_t *lut);

/* Initialization */

static int      qspi_hw_initialize(struct kinetis_qspidev_s *priv);

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI
/* QSPI0 driver operations */

static const struct kqspi_ops_s g_qspi0ops =
{
  .lock              = qspi_lock,
  .setfrequency      = qspi_setfrequency,
  .command           = qspi_command,
  .alloc             = qspi_alloc,
  .free              = qspi_free,
  .setconfig         = qspi_setconfig,
  .setlut            = qspi_setlut
};

/* This is the overall state of the QSPI0 controller */

static struct kinetis_qspidev_s g_qspi0dev =
{
  .qspi            =
  {
    .ops             = &g_qspi0ops,
  },
  .base              = KINETIS_QSPI0C_BASE,
  .intf              = 0,
#ifdef CONFIG_KINETIS_QSPI_DMA
  .candma            = KINETIS_QSPI0_DMA,
  .rxintf            = XDMACH_QSPI_RX,
  .txintf            = XDMACH_QSPI_TX,
#endif
};
#endif /* CONFIG_KINETIS_QSPI */

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: qspi_checkreg
 *
 * Description:
 *   Check if the current register access is a duplicate of the preceding.
 *
 * Input Parameters:
 *   value   - The value to be written
 *   address - The address of the register to write to
 *
 * Returned Value:
 *   true:  This is the first register access of this type.
 *   flase: This is the same as the preceding register access.
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_REGDEBUG
static bool qspi_checkreg(struct kinetis_qspidev_s *priv, bool wr,
                          uint32_t value, uint32_t address)
{
  if (wr      == priv->wrlast &&     /* Same kind of access? */
      value   == priv->valuelast &&  /* Same value? */
      address == priv->addresslast)  /* Same address? */
    {
      /* Yes, then just keep a count of the number of times we did this. */

      priv->ntimes++;
      return false;
    }
  else
    {
      /* Did we do the previous operation more than once? */

      if (priv->ntimes > 0)
        {
          /* Yes... show how many times we did it */

          spiinfo("...[Repeats %d times]...\n", priv->ntimes);
        }

      /* Save information about the new access */

      priv->wrlast      = wr;
      priv->valuelast   = value;
      priv->addresslast = address;
      priv->ntimes      = 0;
    }

  /* Return true if this is the first time that we have done this operation */

  return true;
}
#endif

/****************************************************************************
 * Name: qspi_getreg
 *
 * Description:
 *  Read an QSPI register
 *
 ****************************************************************************/

static inline uint32_t qspi_getreg(struct kinetis_qspidev_s *priv,
                                  unsigned int offset)
{
  uint32_t address = priv->base + offset;
  uint32_t value = getreg32(address);

#ifdef CONFIG_KINETIS_QSPI_REGDEBUG
  if (qspi_checkreg(priv, false, value, address))
    {
      spiinfo("%08x->%08x\n", address, value);
    }
#endif

  return value;
}

/****************************************************************************
 * Name: qspi_putreg
 *
 * Description:
 *  Write a value to an QSPI register
 *
 ****************************************************************************/

static inline void qspi_putreg(struct kinetis_qspidev_s *priv, uint32_t value,
                              unsigned int offset)
{
  uint32_t address = priv->base + offset;

#ifdef CONFIG_KINETIS_QSPI_REGDEBUG
  if (qspi_checkreg(priv, true, value, address))
    {
      spiinfo("%08x<-%08x\n", address, value);
    }
#endif

  putreg32(value, address);
}

/****************************************************************************
 * Name: qspi_dumpregs
 *
 * Description:
 *   Dump the contents of all QSPI registers
 *
 * Input Parameters:
 *   priv - The QSPI controller to dump
 *   msg - Message to print before the register data
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_DEBUG_SPI_INFO
static void qspi_dumpregs(struct kinetis_qspidev_s *priv, const char *msg)
{
  spiinfo("%s:\n", msg);
  spiinfo("    MCR:%08x   IPCR:%08x FLSHCR:%08x  SOCCR:%08x\n",
         getreg32(priv->base + KINETIS_QSPI_MCR_OFFSET),
         getreg32(priv->base + KINETIS_QSPI_IPCR_OFFSET),
         getreg32(priv->base + KINETIS_QSPI_FLSHCR_OFFSET),
         getreg32(priv->base + KINETIS_QSPI_SOCCR_OFFSET));
  spiinfo("     SR:%08x     FR:%08x   RSER:%08x\n",
         getreg32(priv->base + KINETIS_QSPI_SR_OFFSET),
         getreg32(priv->base + KINETIS_QSPI_FR_OFFSET),
         getreg32(priv->base + KINETIS_QSPI_RSER_OFFSET));
}
#endif

/****************************************************************************
 * Name: qspi_dma_sampleinit
 *
 * Description:
 *   Initialize sampling of DMA registers (if CONFIG_KINETIS_QSPI_DMADEBUG)
 *
 * Input Parameters:
 *   priv - QSPI driver instance
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_DMADEBUG
static void qspi_dma_sampleinit(struct kinetis_qspidev_s *priv)
{
  /* Put contents of register samples into a known state */

  memset(priv->dmaregs, 0xff, DMA_NSAMPLES * sizeof(struct kinetis_dmaregs_s));

  /* Then get the initial samples */

  kinetis_dmasample(priv->dmach, &priv->dmaregs[DMA_INITIAL]);
}
#endif

/****************************************************************************
 * Name: qspi_dma_sampledone
 *
 * Description:
 *   Dump sampled DMA registers
 *
 * Input Parameters:
 *   priv - QSPI driver instance
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_DMADEBUG
static void qspi_dma_sampledone(struct kinetis_qspidev_s *priv)
{
  /* Sample the final registers */

  kinetis_dmasample(priv->dmach, &priv->dmaregs[DMA_END_TRANSFER]);

  /* Then dump the sampled DMA registers */

  /* Initial register values */

  kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_INITIAL],
              "Initial Registers");

  /* Register values after DMA setup */

  kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_AFTER_SETUP],
              "After DMA Setup");

  /* Register values after DMA start */

  kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_AFTER_START],
              "After DMA Start");

  /* Register values at the time of the TX and RX DMA callbacks
   * -OR- DMA timeout.
   *
   * If the DMA timed out, then there will not be any RX DMA
   * callback samples.  There is probably no TX DMA callback
   * samples either, but we don't know for sure.
   */

  if (priv->result == -ETIMEDOUT)
    {
      kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_TIMEOUT],
                  "At DMA timeout");
    }
  else
    {
      kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_CALLBACK],
                  "At DMA callback");
    }

  kinetis_dmadump(priv->dmach, &priv->dmaregs[DMA_END_TRANSFER],
              "At End-of-Transfer");
}
#endif

/****************************************************************************
 * Name: qspi_dma_timeout
 *
 * Description:
 *   The watchdog timeout setup when a has expired without completion of a
 *   DMA.
 *
 * Input Parameters:
 *   arg    - The argument
 *
 * Returned Value:
 *   None
 *
 * Assumptions:
 *   Always called from the interrupt level with interrupts disabled.
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_DMA
static void qspi_dma_timeout(wdparm_t arg)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)arg;
  DEBUGASSERT(priv != NULL);

  /* Sample DMA registers at the time of the timeout */

  qspi_dma_sample(priv, DMA_CALLBACK);

  /* Report timeout result, perhaps overwriting any failure reports from
   * the TX callback.
   */

  priv->result = -ETIMEDOUT;

  /* Then wake up the waiting thread */

  nxsem_post(&priv->dmawait);
}
#endif

/****************************************************************************
 * Name: qspi_dma_callback
 *
 * Description:
 *   This callback function is invoked at the completion of the QSPI RX DMA.
 *
 * Input Parameters:
 *   handle - The DMA handler
 *   arg - A pointer to the chip select structure
 *   result - The result of the DMA transfer
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_DMA
static void qspi_dma_callback(DMA_HANDLE handle, void *arg, int result)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)arg;
  DEBUGASSERT(priv != NULL);

  /* Cancel the watchdog timeout */

  wd_cancel(&priv->dmadog);

  /* Sample DMA registers at the time of the callback */

  qspi_dma_sample(priv, DMA_CALLBACK);

  /* Report the result of the transfer only if the TX callback has not
   * already reported an error.
   */

  if (priv->result == -EBUSY)
    {
      /* Save the result of the transfer if no error was previously
       * reported
       */

      priv->result = result;
    }

  /* Then wake up the waiting thread */

  nxsem_post(&priv->dmawait);
}
#endif

/****************************************************************************
 * Name: qspi_regaddr
 *
 * Description:
 *   Return the address of an QSPI register
 *
 ****************************************************************************/

#ifdef CONFIG_KINETIS_QSPI_DMA
static inline uintptr_t qspi_regaddr(struct kinetis_qspidev_s *priv,
                                    unsigned int offset)
{
  return priv->base + offset;
}
#endif

/****************************************************************************
 * Name: qspi_memcpy
 *
 * Description:
 *   32-bit version of memcpy.
 *
 * Input Parameters:
 *   dest   - Destination address of the copy
 *   src    - Source address of the copy
 *   buflen - The number of 32-bit words to copy.
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static void qspi_memcpy(uint8_t *dest, const uint8_t *src, size_t buflen)
{
  /* The size of the SPI transfer is equal to the bus access width.
   * 8-bit transfers should result in in 8-bit SPI accesses.
   */

  for (; buflen > 0; buflen--)
    {
      *dest++ = *src++;
    }
}

/****************************************************************************
 * Name: qspi_lock
 *
 * Description:
 *   On QSPI buses where there are multiple devices, it will be necessary to
 *   lock QSPI to have exclusive access to the buses for a sequence of
 *   transfers.  The bus should be locked before the chip is selected. After
 *   locking the QSPI bus, the caller should then also call the setfrequency,
 *   setbits, and setmode methods to make sure that the QSPI is properly
 *   configured for the device.  If the QSPI bus is being shared, then it
 *   may have been left in an incompatible state.
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   lock - true: Lock QSPI bus, false: unlock QSPI bus
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

static int qspi_lock(struct kqspi_dev_s *dev, bool lock)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)dev;
  int ret;

  spiinfo("lock=%d\n", lock);
  if (lock)
    {
      ret = nxsem_wait_uninterruptible(&priv->exclsem);
    }
  else
    {
      ret = nxsem_post(&priv->exclsem);
    }

  return ret;
}

/****************************************************************************
 * Name: qspi_setfrequency
 *
 * Description:
 *   Set the QSPI frequency.
 *
 * Input Parameters:
 *   dev -       Device-specific state data
 *   frequency - The QSPI frequency requested
 *
 * Returned Value:
 *   Returns the actual frequency selected
 *
 ****************************************************************************/

static uint32_t qspi_setfrequency(struct kqspi_dev_s *dev, uint32_t frequency)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)dev;
  uint32_t actual;
  uint32_t scbr;
  uint32_t regval;

  spiinfo("frequency=%d\n", frequency);
  DEBUGASSERT(priv);

  /* Check if the requested frequency is the same as the frequency
   * selection
   */

  if (priv->frequency == frequency)
    {
      /* We are already at this frequency.  Return the actual. */

      return priv->actual;
    }

  /* Configure QSPI to a frequency as close as possible to the requested
   * frequency.
   *
   *   QSCK frequency = QSPI_CLK / SCBR, or SCBR = QSPI_CLK / frequency
   *
   * Where SCBR can have the range 1 to 256 and the SCR register field holds
   * SCBR - 1.  NOTE that a "ceiling" type of calculation is performed.
   * 'frequency' is treated as a not-to-exceed value.
   */

  scbr = (frequency + SAM_QSPI_CLOCK - 1) / frequency;

  /* Make sure that the divider is within range */

  if (scbr < 1)
    {
      scbr = 1;
    }
  else if (scbr > 256)
    {
      scbr = 256;
    }

  /* Save the new SCBR value (minus one) */

  regval  = qspi_getreg(priv, SAM_QSPI_SCR_OFFSET);
  regval &= ~(QSPI_SCR_SCBR_MASK | QSPI_SCR_DLYBS_MASK);
  regval |= (scbr - 1) << QSPI_SCR_SCBR_SHIFT;

  qspi_putreg(priv, regval, SAM_QSPI_SCR_OFFSET);

  /* Calculate the new actual frequency */

  actual = SAM_QSPI_CLOCK / scbr;
  spiinfo("SCBR=%d actual=%d\n", scbr, actual);

  /* Save the frequency setting */

  priv->frequency = frequency;
  priv->actual    = actual;

  spiinfo("Frequency %d->%d\n", frequency, actual);
  return actual;
}

/****************************************************************************
 * Name: qspi_command
 *
 * Description:
 *   Perform one QSPI data transfer
 *
 * Input Parameters:
 *   dev     - Device-specific state data
 *   cmdinfo - Describes the command transfer to be performed.
 *
 * Returned Value:
 *   Zero (OK) on SUCCESS, a negated errno on value of failure
 *
 ****************************************************************************/

static int qspi_command(struct kqspi_dev_s *dev,
                        struct kqspi_cmdinfo_s *cmdinfo)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)dev;
  uint32_t regval;
  uint32_t ifr;

  DEBUGASSERT(priv != NULL && cmdinfo != NULL);

#ifdef CONFIG_DEBUG_SPI_INFO
  spiinfo("Transfer %s:\n", QSPICMD_ISIP(cmdinfo->flags)?"IP":"AHB");
  spiinfo("  flags: %02x\n", cmdinfo->flags);
  spiinfo("  lut: %04x\n", cmdinfo->lutindex);

  if (QSPICMD_ISADDRESS(cmdinfo->flags))
    {
      spiinfo("  address: %08lx\n",
              (unsigned long)cmdinfo->addr);
    }

  if (QSPICMD_ISDATA(cmdinfo->flags))
    {
      spiinfo("  %s Data:\n",
              QSPICMD_ISWRITE(cmdinfo->flags) ? "Write" : "Read");
      spiinfo("    buffer/length: %p/%d\n",
              cmdinfo->buffer, cmdinfo->buflen);
    }
#endif

  DEBUGASSERT(cmdinfo->cmd < 256);

  /* Write the instruction address register */

  ifr = 0;
  if (QSPICMD_ISADDRESS(cmdinfo->flags))
    {
      DEBUGASSERT(cmdinfo->addrlen == 3 || cmdinfo->addrlen == 4);

      /* Set the address in the IAR.  This is required only if the
       * instruction frame includes an address, but no data.  When data is
       * preset, the address of the instruction is determined by the address
       * of QSPI memory accesses, and not by the content of the IAR.
       */

      qspi_putreg(priv, cmdinfo->addr, SAM_QSPI_IAR_OFFSET);

      /* Set/clear the address enable bit and the address size in the IFR */

      ifr |= QSPI_IFR_ADDREN;

      if (cmdinfo->addrlen == 3)
        {
          ifr |= QSPI_IFR_ADDRL_24BIT;
        }
      else if (cmdinfo->addrlen == 4)
        {
          ifr |= QSPI_IFR_ADDRL_32BIT;
        }
      else
        {
          return -EINVAL;
        }
    }

  /* Write the Instruction code register:
   *
   *  QSPI_ICR_INST(cmd)  8-bit command
   *  QSPI_ICR_OPT(0)     No option
   */

  regval =  QSPI_ICR_INST(cmdinfo->cmd) | QSPI_ICR_OPT(0);
  qspi_putreg(priv, regval, SAM_QSPI_ICR_OFFSET);

  /* Does data accompany the command? */

  if (QSPICMD_ISDATA(cmdinfo->flags))
    {
      DEBUGASSERT(cmdinfo->buffer != NULL && cmdinfo->buflen > 0);
      DEBUGASSERT(IS_ALIGNED(cmdinfo->buffer));

      /* Write Instruction Frame Register:
       *
       *   QSPI_IFR_WIDTH_SINGLE  Instruction=single bit/Data single bit
       *   QSPI_IFR_INSTEN=1      Instruction Enable
       *   QSPI_IFR_ADDREN=?      (See logic above)
       *   QSPI_IFR_OPTEN=0       Option Disable
       *   QSPI_IFR_DATAEN=1      Data Enable
       *   QSPI_IFR_OPTL_*        Not used (zero)
       *   QSPI_IFR_ADDRL=0       Not used (zero)
       *   QSPI_IFR_TFRTYP_WRITE  Write transfer into serial memory, OR
       *   QSPI_IFR_TFRTYP_READ   Read transfer from serial memory
       *   QSPI_IFR_CRM=0         Not continuous read
       *   QSPI_IFR_NBDUM(0)      No dummy cycles
       */

      ifr |= QSPI_IFR_WIDTH_SINGLE | QSPI_IFR_INSTEN | QSPI_IFR_DATAEN |
             QSPI_IFR_NBDUM(0);

      /* Read or write operation? */

      if (QSPICMD_ISWRITE(cmdinfo->flags))
        {
          /* Set write data operation
           *
           * Write the IFR to the hardware.  If the instructrion frame
           * includes data, writing to the IFR does not trigger the
           * instruction frame transfer.  Rather, the instruction frame
           * is triggered by the first access to QSPI memory.
           */

          ifr |= QSPI_IFR_TFRTYP_WRITE;
          qspi_putreg(priv, ifr, SAM_QSPI_IFR_OFFSET);

          /* Read QSPI_IFR (dummy read) to synchronize APB and AHB
           * accesses.
           */

          qspi_getreg(priv, SAM_QSPI_IFR_OFFSET);

          /* Copy the data to write to QSPI_RAM */

          qspi_memcpy((uint8_t *)SAM_QSPIMEM_BASE,
                      (const uint8_t *)cmdinfo->buffer, cmdinfo->buflen);
        }
      else
        {
          /* Set read data operation
           *
           * Write the IFR to the hardware.  If the instructrion frame
           * includes data, writing to the IFR does not trigger the
           * instruction frame transfer.  Rather, the instruction frame
           * is triggered by the first access to QSPI memory.
           */

          ifr |= QSPI_IFR_TFRTYP_READ;
          qspi_putreg(priv, ifr, SAM_QSPI_IFR_OFFSET);

          /* Read QSPI_IFR (dummy read) to synchronize APB and AHB
           * accesses.
           */

          qspi_getreg(priv, SAM_QSPI_IFR_OFFSET);

          /* Copy the data from QSPI memory into the user buffer */

          qspi_memcpy((uint8_t *)cmdinfo->buffer,
                      (const uint8_t *)SAM_QSPIMEM_BASE, cmdinfo->buflen);
        }

      MEMORY_SYNC();

      /* Indicate the end of the transfer as soon as the transmission
       * registers are empty.
       */

      while ((qspi_getreg(priv, SAM_QSPI_SR_OFFSET) & QSPI_INT_TXEMPTY)
             == 0);

      qspi_putreg(priv, QSPI_CR_LASTXFER, SAM_QSPI_CR_OFFSET);

      /* Fall through to INSTRE wait */
    }
  else
    {
      /* Write Instruction Frame Register:
       *
       *   QSPI_IFR_WIDTH_SINGLE  Instruction=single bit/Data single bit
       *   QSPI_IFR_INSTEN=1      Instruction Enable
       *   QSPI_IFR_ADDREN=?      (See logic above)
       *   QSPI_IFR_OPTEN=0       Option Disable
       *   QSPI_IFR_DATAEN=0      Data Disable
       *   QSPI_IFR_OPTL_*        Not used (zero)
       *   QSPI_IFR_ADDRL=0       Not used (zero)
       *   QSPI_IFR_TFRTYP_READ   Shouldn't matter
       *   QSPI_IFR_CRM=0         Not continuous read
       *   QSPI_IFR_NBDUM(0)      No dummy cycles
       */

      ifr |= QSPI_IFR_WIDTH_SINGLE | QSPI_IFR_INSTEN | QSPI_IFR_TFRTYP_READ |
             QSPI_IFR_NBDUM(0);
      qspi_putreg(priv, ifr, SAM_QSPI_IFR_OFFSET);

      MEMORY_SYNC();

      /* If the insruction frame does not include data, writing to the IFR
       * triggers sending of the instruction frame. Fall through to INSTRE
       * wait.
       */
    }

  /* When the command has been sent, Instruction End Status (INTRE) will be
   * set in the QSPI status register.
   */

  while ((qspi_getreg(priv, SAM_QSPI_SR_OFFSET) & QSPI_SR_INSTRE) == 0);

  return OK;
}

/****************************************************************************
 * Name: qspi_memory
 *
 * Description:
 *   Perform one QSPI memory transfer
 *
 * Input Parameters:
 *   dev     - Device-specific state data
 *   meminfo - Describes the memory transfer to be performed.
 *
 * Returned Value:
 *   Zero (OK) on SUCCESS, a negated errno on value of failure
 *
 ****************************************************************************/

static int qspi_memory(struct kqspi_dev_s *dev,
                       struct kqspi_config_s *config)
{
  struct kinetis_qspidev_s *priv = (struct kinetis_qspidev_s *)dev;

  DEBUGASSERT(priv != NULL && meminfo != NULL);

  spiinfo("Transfer:\n");
  spiinfo("  flags: %02x\n", meminfo->flags);
  spiinfo("  cmd: %04x\n", meminfo->cmd);
  spiinfo("  address/length: %08lx/%d\n",
         (unsigned long)meminfo->addr, meminfo->addrlen);
  spiinfo("  %s Data:\n",
          QSPIMEM_ISWRITE(meminfo->flags) ? "Write" : "Read");
  spiinfo("    buffer/length: %p/%d\n", meminfo->buffer, meminfo->buflen);

#ifdef CONFIG_KINETIS_QSPI_DMA
  /* Can we perform DMA?  Should we perform DMA? */

  if (priv->candma &&
      meminfo->buflen > CONFIG_KINETIS_QSPI_DMATHRESHOLD &&
      IS_ALIGNED((uintptr_t)meminfo->buffer) &&
      IS_ALIGNED(meminfo->buflen))
    {
      return qspi_memory_dma(priv, meminfo);
    }
  else
#endif
    {
      return qspi_memory_nodma(priv, meminfo);
    }
}

/****************************************************************************
 * Name: qspi_alloc
 *
 * Description:
 *   Allocate a buffer suitable for DMA data transfer
 *
 * Input Parameters:
 *   dev    - Device-specific state data
 *   buflen - Buffer length to allocate in bytes
 *
 * Returned Value:
 *   Address of the allocated memory on success; NULL is returned on any
 *   failure.
 *
 ****************************************************************************/

static FAR void *qspi_alloc(FAR struct kqspi_dev_s *dev, size_t buflen)
{
  /* Here we exploit the internal knowledge the kmm_malloc() will return
   * memory aligned to 64-bit addresses.  The buffer length must be large
   * enough to hold the rested buflen in units a 32-bits.
   */

  return kmm_malloc(ALIGN_UP(buflen));
}

/****************************************************************************
 * Name: QSPI_FREE
 *
 * Description:
 *   Free memory returned by QSPI_ALLOC
 *
 * Input Parameters:
 *   dev    - Device-specific state data
 *   buffer - Buffer previously allocated via QSPI_ALLOC
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

static void qspi_free(FAR struct kqspi_dev_s *dev, FAR void *buffer)
{
  if (buffer)
    {
      kmm_free(buffer);
    }
}

/****************************************************************************
 * Name: qspi_hw_initialize
 *
 * Description:
 *   Initialize the QSPI peripheral from hardware reset.
 *
 * Input Parameters:
 *   priv - Device state structure.
 *
 * Returned Value:
 *   Zero (OK) on SUCCESS, a negated errno on value of failure
 *
 ****************************************************************************/

static int qspi_hw_initialize(struct kinetis_qspidev_s *priv)
{
  uint32_t regval;

  /* Disable the QSPI */

  qspi_putreg(priv, QSPI_CR_QSPIDIS, SAM_QSPI_CR_OFFSET);
  while ((qspi_getreg(priv, SAM_QSPI_SR_OFFSET) & QSPI_SR_QSPIENS) != 0);

  /* Reset the QSPI (twice) */

  qspi_putreg(priv, QSPI_CR_SWRST, SAM_QSPI_CR_OFFSET);
  qspi_putreg(priv, QSPI_CR_SWRST, SAM_QSPI_CR_OFFSET);

  /* Configure the QSPI
   *
   *   QSPI_MR_SMM             - Serial Memory Mode
   *   QSPI_MR_CSMODE_LASTXFER - CS de-asserted when LASTXFER transferred
   */

  regval = QSPI_MR_SMM;
  qspi_putreg(priv, regval, SAM_QSPI_MR_OFFSET);

  regval |= QSPI_MR_CSMODE_LASTXFER;
  qspi_putreg(priv, regval, SAM_QSPI_MR_OFFSET);

  /* Set up the initial QSPI clock mode:
   *
   * Mode 0:  CPOL=0; CPHA=0
   */

  regval  = qspi_getreg(priv, SAM_QSPI_SCR_OFFSET);
  regval &= ~(QSPI_SCR_CPOL | QSPI_SCR_CPHA);
  qspi_putreg(priv, regval, SAM_QSPI_SCR_OFFSET);

  regval |= QSPI_SCR_SCBR(1);
  qspi_putreg(priv, regval, SAM_QSPI_SCR_OFFSET);

  /* 8-bit mode */

  regval  = qspi_getreg(priv, SAM_QSPI_MR_OFFSET);
  regval &= ~QSPI_MR_NBBITS_MASK;
  regval |= QSPI_MR_NBBITS_8BIT;
  qspi_putreg(priv, regval, SAM_QSPI_MR_OFFSET);

  priv->nbits = 8;

  /* Enable QSPI */

  qspi_putreg(priv, QSPI_CR_QSPIEN, SAM_QSPI_CR_OFFSET);
  while ((qspi_getreg(priv, SAM_QSPI_SR_OFFSET) & QSPI_SR_QSPIENS) == 0);

  /* Flush any pending transfers */

  qspi_getreg(priv, SAM_QSPI_SR_OFFSET);
  qspi_getreg(priv, SAM_QSPI_RDR_OFFSET);

  qspi_dumpregs(priv, "After initialization");
  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: kinetis_qspi_initialize
 *
 * Description:
 *   Initialize the selected QSPI port in master mode
 *
 * Input Parameters:
 *   intf - Interface number(must be zero)
 *
 * Returned Value:
 *   Valid QSPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct kqspi_dev_s *kinetis_qspi_initialize(int intf)
{
  struct kinetis_qspidev_s *priv;
  int ret;

  /* The supported SAM parts have only a single QSPI port */

  spiinfo("intf: %d\n", intf);
  DEBUGASSERT(intf >= 0 && intf < KINETIS_NQSPI);

  /* Select the QSPI interface */

#ifdef CONFIG_KINETIS_QSPI
  if (intf == 0)
    {
      /* If this function is called multiple times, the following operations
       * will be performed multiple times.
       */

      /* Select QSPI0 */

      priv = &g_qspi0dev;

      /* Enable clocking to the QSPI peripheral */

      kinetis_qspi_enableclk();

      /* Configure multiplexed pins as connected on the board. */

      kinetis_configgpio(GPIO_QSPI_CS);
      kinetis_configgpio(GPIO_QSPI_IO0);
      kinetis_configgpio(GPIO_QSPI_IO1);
      kinetis_configgpio(GPIO_QSPI_IO2);
      kinetis_configgpio(GPIO_QSPI_IO3);
      kinetis_configgpio(GPIO_QSPI_SCK);
    }
  else
#endif
    {
      spierr("ERROR: QSPI%d not supported\n", intf);
      return NULL;
    }

  /* Has the QSPI hardware been initialized? */

  if (!priv->initialized)
    {
      /* No perform one time initialization */

      /* Initialize the QSPI semaphore that enforces mutually exclusive
       * access to the QSPI registers.
       */

      nxsem_init(&priv->exclsem, 0, 1);

#ifdef CONFIG_KINETIS_QSPI_DMA
      /* Pre-allocate DMA channels. */

      if (priv->candma)
        {
          priv->dmach = kinetis_dmachannel(0, 0);
          if (!priv->dmach)
            {
              spierr("ERROR: Failed to allocate the DMA channel\n");
              priv->candma = false;
            }
        }

      /* Initialize the QSPI semaphore that is used to wake up the waiting
       * thread when the DMA transfer completes.  This semaphore is used for
       * signaling and, hence, should not have priority inheritance enabled.
       */

      nxsem_init(&priv->dmawait, 0, 0);
      nxsem_set_protocol(&priv->dmawait, SEM_PRIO_NONE);
#endif

      /* Perform hardware initialization.  Puts the QSPI into an active
       * state.
       */

      ret = qspi_hw_initialize(priv);
      if (ret < 0)
        {
          spierr("ERROR: Failed to initialize QSPI hardware\n");
          goto errout;
        }

      /* Enable interrupts at the NVIC */

      priv->initialized = true;
    }

  return &priv->qspi;

errout:
#ifdef CONFIG_KINETIS_QSPI_DMA
  nxsem_destroy(&priv->dmawait);
  if (priv->dmach)
    {
      kinetis_dmafree(priv->dmach);
      priv->dmach = NULL;
    }
#endif

  nxsem_destroy(&priv->exclsem);
  return NULL;
}
#endif /* CONFIG_KINETIS_QSPI */
