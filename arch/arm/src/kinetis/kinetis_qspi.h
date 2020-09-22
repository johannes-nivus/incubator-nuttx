/****************************************************************************************************
 * arch/arm/src/kinetis/kinetis_qspi.h
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

#ifndef __ARCH_ARM_SRC_KINETIS_KINETIS_QSPI_H
#define __ARCH_ARM_SRC_KINETIS_KINETIS_QSPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Access macros ************************************************************/

/****************************************************************************
 * Name: QSPI_LOCK
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
 *   lock - true: Lock qspi bus, false: unlock QSPI bus
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#define QSPI_LOCK(d,l) (d)->ops->lock(d,l)

/****************************************************************************
 * Name: QSPI_SETFREQUENCY
 *
 * Description:
 *   Set the QSPI frequency. Required.
 *
 * Input Parameters:
 *   dev -       Device-specific state data
 *   frequency - The QSPI frequency requested
 *
 * Returned Value:
 *   Returns the actual frequency selected
 *
 ****************************************************************************/

#define QSPI_SETFREQUENCY(d,f) ((d)->ops->setfrequency(d,f))

/****************************************************************************
 * Name: QSPI_CONFIG
 *
 * Description:
 *   Set a QSPI config.
 *
 * Input Parameters:
 *   dev -  Device-specific state data
 *   conf - Flash-specific config
 *
 * Returned Value:
 *   none
 *
 ****************************************************************************/

#define QSPI_SETCONFIG(d,c) (d)->ops->setconfig(d,c)

/****************************************************************************
 * Name: QSPI_SETLUT
 *
 * Description:
 *   Set a QSPI lookuptable.
 *
 * Input Parameters:
 *   dev -  Device-specific state data
 *   lut - Flash-specific command table
 *
 * Returned Value:
 *   none
 *
 ****************************************************************************/

#define QSPI_SETLUT(d,l) (d)->ops->setlut(d,l)

/****************************************************************************
 * Name: QSPI_COMMAND
 *
 * Description:
 *   Perform one QSPI command transfer
 *
 * Input Parameters:
 *   dev     - Device-specific state data
 *   cmdinfo - Describes the command transfer to be performed.
 *
 * Returned Value:
 *   Zero (OK) on SUCCESS, a negated errno on value of failure
 *
 ****************************************************************************/

#define QSPI_COMMAND(d,c) (d)->ops->command(d,c)

/* QSPI Command Transfer Flags */

#define QSPICMD_IPCMD         (1 << 0)  /* Bit 0: IP command else AHB */
#define QSPICMD_READDATA      (1 << 1)  /* Bit 1: Enable read data transfer */
#define QSPICMD_WRITEDATA     (1 << 2)  /* Bit 2: Enable write data transfer */
#define QSPICMD_ADDRESS       (1 << 0)  /* Bit 3: Enable address transfer */

#define QSPICMD_ISIPCMD(f)    (((f) & QSPICMD_IPCMD) != 0)
#define QSPICMD_ISDATA(f)     (((f) & (QSPICMD_READDATA \
                                     | QSPICMD_WRITEDATA)) != 0)
#define QSPICMD_ISREAD(f)     (((f) & QSPICMD_READDATA) != 0)
#define QSPICMD_ISWRITE(f)    (((f) & QSPICMD_WRITEDATA) != 0)
#define QSPICMD_ISADDRESS(f)  (((f) & QSPICMD_ADDRESS) != 0)

/****************************************************************************
 * Name: QSPI_MEMORY
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

#define QSPI_MEMORY(d,m) (d)->ops->memory(d,m)

/****************************************************************************
 * Name: QSPI_ALLOC
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

#define QSPI_ALLOC(d,b) (d)->ops->alloc(d,b)

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

#define QSPI_FREE(d,b) (d)->ops->free(d,b)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* This structure describes one command transfer */

struct kqspi_cmdinfo_s
{
  uint8_t   flags;       /* See QSPICMD_* definitions */
  uint8_t   lutindex;    /* Command index in lookup table */
  uint16_t  buflen;      /* Data buffer length in bytes (if QSPICMD_DATA) */
  uint32_t  addr;        /* Address (if QSPICMD_ADDRESS) */
  FAR void *buffer;      /* Data buffer (if QSPICMD_DATA) */
};

/* This structure describes a flashconfig */

struct kqspi_config_s
{
};

/* The QSPI vtable */

struct kqspi_dev_s;
struct kqspi_ops_s
{
  CODE int       (*lock)(FAR struct kqspi_dev_s *dev, bool lock);
  CODE uint32_t  (*setfrequency)(FAR struct kqspi_dev_s *dev,
                    uint32_t frequency);
  CODE int       (*command)(FAR struct kqspi_dev_s *dev,
                    FAR struct kqspi_cmdinfo_s *cmdinfo);
  CODE FAR void *(*alloc)(FAR struct kqspi_dev_s *dev, size_t buflen);
  CODE void      (*free)(FAR struct kqspi_dev_s *dev, FAR void *buffer);
  CODE void      (*setconfig)(FAR struct kqspi_dev_s *dev,
                    FAR struct kqspi_config_s *conf);
  CODE void      (*setlut)(FAR struct kqspi_dev_s *dev, FAR uint32_t *lut);
};

/* QSPI private data.  This structure only defines the initial fields of the
 * structure visible to the QSPI client.  The specific implementation may
 * add additional, device specific fields
 */

struct kqspi_dev_s
{
  FAR const struct kqspi_ops_s *ops;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
}
#endif
#endif /* __ARCH_ARM_SRC_KINETIS_KINETIS_QSPI_H */
