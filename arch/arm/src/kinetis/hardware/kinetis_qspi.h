/****************************************************************************************************
 * arch/arm/src/kinetis/hardware/kinetis_qspi.h
 *
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

#ifndef __ARCH_ARM_SRC_KINETIS_HARDWARE_KINETIS_QSPI_H
#define __ARCH_ARM_SRC_KINETIS_HARDWARE_KINETIS_QSPI_H

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <nuttx/config.h>

#include "chip.h"

/****************************************************************************************************
 * Pre-processor Definitions
 ****************************************************************************************************/

#define KINETIS_QSPI_TXFIFO_SIZE32   16

/* Register Offsets *********************************************************************************/

#define KINETIS_QSPI_MCR_OFFSET      0x0000 /* Module Configuration Register */
#define KINETIS_QSPI_IPCR_OFFSET     0x0008 /* IP Configuration Register */
#define KINETIS_QSPI_FLSHCR_OFFSET   0x000c /* Flash Configuration Register */
#define KINETIS_QSPI_BUF0CR_OFFSET   0x0010 /* Buffer0 Configuration Register */
#define KINETIS_QSPI_BUF1CR_OFFSET   0x0014 /* Buffer1 Configuration Register */
#define KINETIS_QSPI_BUF2CR_OFFSET   0x0018 /* Buffer2 Configuration Register */
#define KINETIS_QSPI_BUF3CR_OFFSET   0x001c /* Buffer3 Configuration Register */
#define KINETIS_QSPI_BFGENCR_OFFSET  0x0020 /* Buffer Generic Configuration Register */
#define KINETIS_QSPI_SOCCR_OFFSET    0x0024 /* SOC Configuration Register */
#define KINETIS_QSPI_BUF0IND_OFFSET  0x0030 /* Buffer0 Top Index Register */
#define KINETIS_QSPI_BUF1IND_OFFSET  0x0034 /* Buffer1 Top Index Register */
#define KINETIS_QSPI_BUF2IND_OFFSET  0x0038 /* Buffer2 Top Index Register */
#define KINETIS_QSPI_SFAR_OFFSET     0x0100 /* Serial Flash Address Register */
#define KINETIS_QSPI_SFACR_OFFSET    0x0104 /* Serial Flash Address Configuration Register */
#define KINETIS_QSPI_SMPR_OFFSET     0x0108 /* Sampling Register */
#define KINETIS_QSPI_RBSR_OFFSET     0x010c /* RX Buffer Status Register */
#define KINETIS_QSPI_RBCT_OFFSET     0x0110 /* RX Buffer Control Register */
#define KINETIS_QSPI_TBSR_OFFSET     0x0150 /* TX Buffer Status Register */
#define KINETIS_QSPI_TBDR_OFFSET     0x0154 /* TX Buffer Data Register */
#define KINETIS_QSPI_TBCT_OFFSET     0x0158 /* Tx Buffer Control Register */
#define KINETIS_QSPI_SR_OFFSET       0x015c /* Status Register */
#define KINETIS_QSPI_FR_OFFSET       0x0160 /* Flag Register */
#define KINETIS_QSPI_RSER_OFFSET     0x0164 /* Interrupt and DMA Request Select & Enable Register */
#define KINETIS_QSPI_SPNDST_OFFSET   0x0168 /* Sequence Suspend Status Register */
#define KINETIS_QSPI_SPTRCLR_OFFSET  0x016c /* Sequence Pointer Clear Register */
#define KINETIS_QSPI_SFA1AD_OFFSET   0x0180 /* Serial Flash A1 Top Address */
#define KINETIS_QSPI_SFA2AD_OFFSET   0x0184 /* Serial Flash A2 Top Address */
#define KINETIS_QSPI_SFB1AD_OFFSET   0x0188 /* Serial Flash B1 Top Address */
#define KINETIS_QSPI_SFB2AD_OFFSET   0x018c /* Serial Flash B2 Top Address */
#define KINETIS_QSPI_DLPR_OFFSET     0x0190 /* Data Learn Pattern Register */
#define KINETIS_QSPI_RBDR_OFFSET     0x0200 /* RX Buffer Data Register */
#define KINETIS_QSPI_RBDR0_OFFSET    0x0200 /* RX Buffer Data Register 0 */
#define KINETIS_QSPI_RBDR1_OFFSET    0x0204 /* RX Buffer Data Register 1 */
#define KINETIS_QSPI_RBDR2_OFFSET    0x0208 /* RX Buffer Data Register 2 */
#define KINETIS_QSPI_RBDR3_OFFSET    0x020c /* RX Buffer Data Register 3 */
#define KINETIS_QSPI_RBDR4_OFFSET    0x0210 /* RX Buffer Data Register 4 */
#define KINETIS_QSPI_RBDR5_OFFSET    0x0214 /* RX Buffer Data Register 5 */
#define KINETIS_QSPI_RBDR6_OFFSET    0x0218 /* RX Buffer Data Register 6 */
#define KINETIS_QSPI_RBDR7_OFFSET    0x021c /* RX Buffer Data Register 7 */
#define KINETIS_QSPI_RBDR8_OFFSET    0x0220 /* RX Buffer Data Register 8 */
#define KINETIS_QSPI_RBDR9_OFFSET    0x0224 /* RX Buffer Data Register 9 */
#define KINETIS_QSPI_RBDR10_OFFSET   0x0228 /* RX Buffer Data Register 10 */
#define KINETIS_QSPI_RBDR11_OFFSET   0x022c /* RX Buffer Data Register 11 */
#define KINETIS_QSPI_RBDR12_OFFSET   0x0230 /* RX Buffer Data Register 12 */
#define KINETIS_QSPI_RBDR13_OFFSET   0x0234 /* RX Buffer Data Register 13 */
#define KINETIS_QSPI_RBDR14_OFFSET   0x0238 /* RX Buffer Data Register 14 */
#define KINETIS_QSPI_RBDR15_OFFSET   0x023c /* RX Buffer Data Register 15 */
#define KINETIS_QSPI_LUTKEY_OFFSET   0x0300 /* LUT Key Register */
#define KINETIS_QSPI_LCKCR_OFFSET    0x0304 /* LUT Lock Configuration Register */
#define KINETIS_QSPI_LUT_OFFSET      0x0310 /* Look-up Table register */
#define KINETIS_QSPI_LUT0_OFFSET     0x0310 /* Look-up Table register 0 */
#define KINETIS_QSPI_LUT1_OFFSET     0x0314 /* Look-up Table register 1 */
#define KINETIS_QSPI_LUT2_OFFSET     0x0318 /* Look-up Table register 2 */
#define KINETIS_QSPI_LUT3_OFFSET     0x031c /* Look-up Table register 3 */
#define KINETIS_QSPI_LUT4_OFFSET     0x0320 /* Look-up Table register 4 */
#define KINETIS_QSPI_LUT5_OFFSET     0x0324 /* Look-up Table register 5 */
#define KINETIS_QSPI_LUT6_OFFSET     0x0328 /* Look-up Table register 6 */
#define KINETIS_QSPI_LUT7_OFFSET     0x032c /* Look-up Table register 7 */
#define KINETIS_QSPI_LUT8_OFFSET     0x0330 /* Look-up Table register 8 */
#define KINETIS_QSPI_LUT9_OFFSET     0x0334 /* Look-up Table register 9 */
#define KINETIS_QSPI_LUT10_OFFSET    0x0338 /* Look-up Table register 10 */
#define KINETIS_QSPI_LUT11_OFFSET    0x033c /* Look-up Table register 11 */
#define KINETIS_QSPI_LUT12_OFFSET    0x0340 /* Look-up Table register 12 */
#define KINETIS_QSPI_LUT13_OFFSET    0x0344 /* Look-up Table register 13 */
#define KINETIS_QSPI_LUT14_OFFSET    0x0348 /* Look-up Table register 14 */
#define KINETIS_QSPI_LUT15_OFFSET    0x034c /* Look-up Table register 15 */
#define KINETIS_QSPI_LUT16_OFFSET    0x0350 /* Look-up Table register 16 */
#define KINETIS_QSPI_LUT17_OFFSET    0x0354 /* Look-up Table register 17 */
#define KINETIS_QSPI_LUT18_OFFSET    0x0358 /* Look-up Table register 18 */
#define KINETIS_QSPI_LUT19_OFFSET    0x035c /* Look-up Table register 19 */
#define KINETIS_QSPI_LUT20_OFFSET    0x0360 /* Look-up Table register 20 */
#define KINETIS_QSPI_LUT21_OFFSET    0x0364 /* Look-up Table register 21 */
#define KINETIS_QSPI_LUT22_OFFSET    0x0368 /* Look-up Table register 22 */
#define KINETIS_QSPI_LUT23_OFFSET    0x036c /* Look-up Table register 23 */
#define KINETIS_QSPI_LUT24_OFFSET    0x0370 /* Look-up Table register 24 */
#define KINETIS_QSPI_LUT25_OFFSET    0x0374 /* Look-up Table register 25 */
#define KINETIS_QSPI_LUT26_OFFSET    0x0378 /* Look-up Table register 26 */
#define KINETIS_QSPI_LUT27_OFFSET    0x037c /* Look-up Table register 27 */
#define KINETIS_QSPI_LUT28_OFFSET    0x0380 /* Look-up Table register 28 */
#define KINETIS_QSPI_LUT29_OFFSET    0x0384 /* Look-up Table register 29 */
#define KINETIS_QSPI_LUT30_OFFSET    0x0388 /* Look-up Table register 30 */
#define KINETIS_QSPI_LUT31_OFFSET    0x038c /* Look-up Table register 31 */
#define KINETIS_QSPI_LUT32_OFFSET    0x0390 /* Look-up Table register 32 */
#define KINETIS_QSPI_LUT33_OFFSET    0x0394 /* Look-up Table register 33 */
#define KINETIS_QSPI_LUT34_OFFSET    0x0398 /* Look-up Table register 34 */
#define KINETIS_QSPI_LUT35_OFFSET    0x039c /* Look-up Table register 35 */
#define KINETIS_QSPI_LUT36_OFFSET    0x03a0 /* Look-up Table register 36 */
#define KINETIS_QSPI_LUT37_OFFSET    0x03a4 /* Look-up Table register 37 */
#define KINETIS_QSPI_LUT38_OFFSET    0x03a8 /* Look-up Table register 38 */
#define KINETIS_QSPI_LUT39_OFFSET    0x03ac /* Look-up Table register 39 */
#define KINETIS_QSPI_LUT40_OFFSET    0x03b0 /* Look-up Table register 40 */
#define KINETIS_QSPI_LUT41_OFFSET    0x03b4 /* Look-up Table register 41 */
#define KINETIS_QSPI_LUT42_OFFSET    0x03b8 /* Look-up Table register 42 */
#define KINETIS_QSPI_LUT43_OFFSET    0x03bc /* Look-up Table register 43 */
#define KINETIS_QSPI_LUT44_OFFSET    0x03c0 /* Look-up Table register 44 */
#define KINETIS_QSPI_LUT45_OFFSET    0x03c4 /* Look-up Table register 45 */
#define KINETIS_QSPI_LUT46_OFFSET    0x03c8 /* Look-up Table register 46 */
#define KINETIS_QSPI_LUT47_OFFSET    0x03cc /* Look-up Table register 47 */
#define KINETIS_QSPI_LUT48_OFFSET    0x03d0 /* Look-up Table register 48 */
#define KINETIS_QSPI_LUT49_OFFSET    0x03d4 /* Look-up Table register 49 */
#define KINETIS_QSPI_LUT50_OFFSET    0x03d8 /* Look-up Table register 50 */
#define KINETIS_QSPI_LUT51_OFFSET    0x03dc /* Look-up Table register 51 */
#define KINETIS_QSPI_LUT52_OFFSET    0x03e0 /* Look-up Table register 52 */
#define KINETIS_QSPI_LUT53_OFFSET    0x03e4 /* Look-up Table register 53 */
#define KINETIS_QSPI_LUT54_OFFSET    0x03e8 /* Look-up Table register 54 */
#define KINETIS_QSPI_LUT55_OFFSET    0x03ec /* Look-up Table register 55 */
#define KINETIS_QSPI_LUT56_OFFSET    0x03f0 /* Look-up Table register 56 */
#define KINETIS_QSPI_LUT57_OFFSET    0x03f4 /* Look-up Table register 57 */
#define KINETIS_QSPI_LUT58_OFFSET    0x03f8 /* Look-up Table register 58 */
#define KINETIS_QSPI_LUT59_OFFSET    0x03fc /* Look-up Table register 59 */
#define KINETIS_QSPI_LUT60_OFFSET    0x0400 /* Look-up Table register 60 */
#define KINETIS_QSPI_LUT61_OFFSET    0x0404 /* Look-up Table register 61 */
#define KINETIS_QSPI_LUT62_OFFSET    0x0408 /* Look-up Table register 62 */
#define KINETIS_QSPI_LUT63_OFFSET    0x040c /* Look-up Table register 63 */

/* Register Addresses *******************************************************************************/

#define KINETIS_QSPI_MCR      (KINETIS_QSPI0C_BASE + KINETIS_QSPI_MCR_OFFSET)
#define KINETIS_QSPI_IPCR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_IPCR_OFFSET)
#define KINETIS_QSPI_FLSHCR   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_FLSHCR_OFFSET)
#define KINETIS_QSPI_BUF0CR   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF0CR_OFFSET)
#define KINETIS_QSPI_BUF1CR   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF1CR_OFFSET)
#define KINETIS_QSPI_BUF2CR   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF2CR_OFFSET)
#define KINETIS_QSPI_BUF3CR   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF3CR_OFFSET)
#define KINETIS_QSPI_BFGENCR  (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BFGENCR_OFFSET)
#define KINETIS_QSPI_SOCCR    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SOCCR_OFFSET)
#define KINETIS_QSPI_BUF0IND  (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF0IND_OFFSET)
#define KINETIS_QSPI_BUF1IND  (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF1IND_OFFSET)
#define KINETIS_QSPI_BUF2IND  (KINETIS_QSPI0C_BASE + KINETIS_QSPI_BUF2IND_OFFSET)
#define KINETIS_QSPI_SFAR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFAR_OFFSET)
#define KINETIS_QSPI_SFACR    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFACR_OFFSET)
#define KINETIS_QSPI_SMPR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SMPR_OFFSET)
#define KINETIS_QSPI_RBSR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBSR_OFFSET)
#define KINETIS_QSPI_RBCT     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBCT_OFFSET)
#define KINETIS_QSPI_TBSR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_TBSR_OFFSET)
#define KINETIS_QSPI_TBDR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_TBDR_OFFSET)
#define KINETIS_QSPI_TBCT     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_TBCT_OFFSET)
#define KINETIS_QSPI_SR       (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SR_OFFSET)
#define KINETIS_QSPI_FR       (KINETIS_QSPI0C_BASE + KINETIS_QSPI_FR_OFFSET)
#define KINETIS_QSPI_RSER     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RSER_OFFSET)
#define KINETIS_QSPI_SPNDST   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SPNDST_OFFSET)
#define KINETIS_QSPI_SPTRCLR  (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SPTRCLR_OFFSET)
#define KINETIS_QSPI_SFA1AD   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFA1AD_OFFSET)
#define KINETIS_QSPI_SFA2AD   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFA2AD_OFFSET)
#define KINETIS_QSPI_SFB1AD   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFB1AD_OFFSET)
#define KINETIS_QSPI_SFB2AD   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_SFB2AD_OFFSET)
#define KINETIS_QSPI_DLPR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_DLPR_OFFSET)
#define KINETIS_QSPI_RBDR     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR_OFFSET)
#define KINETIS_QSPI_RBDR0    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR0_OFFSET)
#define KINETIS_QSPI_RBDR1    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR1_OFFSET)
#define KINETIS_QSPI_RBDR2    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR2_OFFSET)
#define KINETIS_QSPI_RBDR3    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR3_OFFSET)
#define KINETIS_QSPI_RBDR4    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR4_OFFSET)
#define KINETIS_QSPI_RBDR5    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR5_OFFSET)
#define KINETIS_QSPI_RBDR6    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR6_OFFSET)
#define KINETIS_QSPI_RBDR7    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR7_OFFSET)
#define KINETIS_QSPI_RBDR8    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR8_OFFSET)
#define KINETIS_QSPI_RBDR9    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR9_OFFSET)
#define KINETIS_QSPI_RBDR10   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR10_OFFSET)
#define KINETIS_QSPI_RBDR11   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR11_OFFSET)
#define KINETIS_QSPI_RBDR12   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR12_OFFSET)
#define KINETIS_QSPI_RBDR13   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR13_OFFSET)
#define KINETIS_QSPI_RBDR14   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR14_OFFSET)
#define KINETIS_QSPI_RBDR15   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_RBDR15_OFFSET)
#define KINETIS_QSPI_LUTKEY   (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUTKEY_OFFSET)
#define KINETIS_QSPI_LCKCR    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LCKCR_OFFSET)
#define KINETIS_QSPI_LUT      (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT_OFFSET)
#define KINETIS_QSPI_LUT0     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT0_OFFSET)
#define KINETIS_QSPI_LUT1     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT1_OFFSET)
#define KINETIS_QSPI_LUT2     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT2_OFFSET)
#define KINETIS_QSPI_LUT3     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT3_OFFSET)
#define KINETIS_QSPI_LUT4     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT4_OFFSET)
#define KINETIS_QSPI_LUT5     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT5_OFFSET)
#define KINETIS_QSPI_LUT6     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT6_OFFSET)
#define KINETIS_QSPI_LUT7     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT7_OFFSET)
#define KINETIS_QSPI_LUT8     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT8_OFFSET)
#define KINETIS_QSPI_LUT9     (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT9_OFFSET)
#define KINETIS_QSPI_LUT10    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT10_OFFSET)
#define KINETIS_QSPI_LUT11    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT11_OFFSET)
#define KINETIS_QSPI_LUT12    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT12_OFFSET)
#define KINETIS_QSPI_LUT13    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT13_OFFSET)
#define KINETIS_QSPI_LUT14    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT14_OFFSET)
#define KINETIS_QSPI_LUT15    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT15_OFFSET)
#define KINETIS_QSPI_LUT16    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT16_OFFSET)
#define KINETIS_QSPI_LUT17    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT17_OFFSET)
#define KINETIS_QSPI_LUT18    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT18_OFFSET)
#define KINETIS_QSPI_LUT19    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT19_OFFSET)
#define KINETIS_QSPI_LUT20    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT20_OFFSET)
#define KINETIS_QSPI_LUT21    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT21_OFFSET)
#define KINETIS_QSPI_LUT22    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT22_OFFSET)
#define KINETIS_QSPI_LUT23    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT23_OFFSET)
#define KINETIS_QSPI_LUT24    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT24_OFFSET)
#define KINETIS_QSPI_LUT25    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT25_OFFSET)
#define KINETIS_QSPI_LUT26    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT26_OFFSET)
#define KINETIS_QSPI_LUT27    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT27_OFFSET)
#define KINETIS_QSPI_LUT28    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT28_OFFSET)
#define KINETIS_QSPI_LUT29    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT29_OFFSET)
#define KINETIS_QSPI_LUT30    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT30_OFFSET)
#define KINETIS_QSPI_LUT31    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT31_OFFSET)
#define KINETIS_QSPI_LUT32    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT32_OFFSET)
#define KINETIS_QSPI_LUT33    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT33_OFFSET)
#define KINETIS_QSPI_LUT34    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT34_OFFSET)
#define KINETIS_QSPI_LUT35    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT35_OFFSET)
#define KINETIS_QSPI_LUT36    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT36_OFFSET)
#define KINETIS_QSPI_LUT37    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT37_OFFSET)
#define KINETIS_QSPI_LUT38    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT38_OFFSET)
#define KINETIS_QSPI_LUT39    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT39_OFFSET)
#define KINETIS_QSPI_LUT40    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT40_OFFSET)
#define KINETIS_QSPI_LUT41    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT41_OFFSET)
#define KINETIS_QSPI_LUT42    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT42_OFFSET)
#define KINETIS_QSPI_LUT43    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT43_OFFSET)
#define KINETIS_QSPI_LUT44    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT44_OFFSET)
#define KINETIS_QSPI_LUT45    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT45_OFFSET)
#define KINETIS_QSPI_LUT46    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT46_OFFSET)
#define KINETIS_QSPI_LUT47    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT47_OFFSET)
#define KINETIS_QSPI_LUT48    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT48_OFFSET)
#define KINETIS_QSPI_LUT49    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT49_OFFSET)
#define KINETIS_QSPI_LUT50    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT50_OFFSET)
#define KINETIS_QSPI_LUT51    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT51_OFFSET)
#define KINETIS_QSPI_LUT52    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT52_OFFSET)
#define KINETIS_QSPI_LUT53    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT53_OFFSET)
#define KINETIS_QSPI_LUT54    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT54_OFFSET)
#define KINETIS_QSPI_LUT55    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT55_OFFSET)
#define KINETIS_QSPI_LUT56    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT56_OFFSET)
#define KINETIS_QSPI_LUT57    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT57_OFFSET)
#define KINETIS_QSPI_LUT58    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT58_OFFSET)
#define KINETIS_QSPI_LUT59    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT59_OFFSET)
#define KINETIS_QSPI_LUT60    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT60_OFFSET)
#define KINETIS_QSPI_LUT61    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT61_OFFSET)
#define KINETIS_QSPI_LUT62    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT62_OFFSET)
#define KINETIS_QSPI_LUT63    (KINETIS_QSPI0C_BASE + KINETIS_QSPI_LUT63_OFFSET)

/* Register Bit Definitions *************************************************************************/

/* QSPI Module Configuration Register */

#define QSPI_MCR_SWRSTSD    (1 << 0)  /* Bit 0:  Software reset for serial flash domain */
#define QSPI_MCR_SWRSTHD    (1 << 1)  /* Bit 1:  Software reset for AHB domain */
#define QSPI_MCR_END_CFG_SHIFT (2)    /* Bits 2-3: Defines the endianness of the QuadSPI module. */
#define QSPI_MCR_END_CFG_MASK  (0x3 << QSPI_MCR_END_CFG_SHIFT)
#  define QSPI_MCR_END_CFG(n)  ((n << QSPI_MCR_END_CFG_SHIFT) & QSPI_MCR_END_CFG_MASK)
                                      /* Bit 4:  Reserved */
#define QSPI_MCR_DQS_LAT_EN (1 << 5)  /* Bit 5:  DQS Latency Enable */
#define QSPI_MCR_DQS_EN     (1 << 6)  /* Bit 6:  DQS enable */
#define QSPI_MCR_DDR_EN     (1 << 7)  /* Bit 7:  DDR mode enable */
                                      /* Bits 8-9: Reserved */
#define QSPI_MCR_CLR_RXF    (1 << 10) /* Bit 10: Clear RX FIFO. Invalidates the RX Buffer.
                                       * This is a self-clearing field. */
#define QSPI_MCR_CLR_TXF    (1 << 11) /* Bit 11: Clear TX FIFO/Buffer. Invalidates the TX Buffer.
                                       * This is a self-clearing field. */
                                      /* Bits 12-13: Reserved */
#define QSPI_MCR_MDIS       (1 << 14) /* Bit 14: Module Disable */
                                      /* Bit 15: Reserved */
#define QSPI_MCR_ISD2FA     (1 << 16) /* Bit 16: Idle Signal Drive IOFA[2] Flash A */
#define QSPI_MCR_ISD3FA     (1 << 17) /* Bit 17: Idle Signal Drive IOFA[3] Flash A */
#define QSPI_MCR_ISD2FB     (1 << 18) /* Bit 18: Idle Signal Drive IOFB[2] Flash B */
#define QSPI_MCR_ISD3FB     (1 << 19) /* Bit 19: Idle Signal Drive IOFB[3] Flash B */
                                      /* Bits 20-23: Reserved */
#define QSPI_MCR_SCLKCFG_SHIFT (24)   /* Bits 24-31: Serial Clock Configuration */
#define QSPI_MCR_SCLKCFG_MASK  (0xff << QSPI_MCR_SCLKCFG_SHIFT)
#  define QSPI_MCR_SCLKCFG(n)  ((n << QSPI_MCR_SCLKCFG_SHIFT) & QSPI_MCR_SCLKCFG_MASK)

/* QSPI IP Configuration Register */

#define QSPI_IPCR_IDATSZ_SHIFT (0) /* Bits 0-15: IP data transfer size. Defines the data transfer
                                    * size in bytes of the IP command. */
#define QSPI_IPCR_IDATSZ_MASK  (0xffff << QSPI_IPCR_IDATSZ_SHIFT)
#  define QSPI_IPCR_IDATSZ(n)  ((n << QSPI_IPCR_IDATSZ_SHIFT) & QSPI_IPCR_IDATSZ_MASK)

#define QSPI_IPCR_PAR_EN (1 << 16) /* Bit 16: When set, a transaction to two serial flash devices
                                    * is triggered in parallel mode */
                                   /* Bits 17-23: Reserved */
#define QSPI_IPCR_SEQID_SHIFT (24) /* Bits 24-27: Points to a sequence in the Look-up table */
#define QSPI_IPCR_SEQID_MASK  (0xf << QSPI_IPCR_SEQID_SHIFT)
#  define QSPI_IPCR_SEQID(n)  ((n << QSPI_IPCR_SEQID_SHIFT) & QSPI_IPCR_SEQID_MASK)
                                   /* Bits 28-31: Reserved */

/* QSPI Flash Configuration Register */

#define QSPI_FLSHCR_TCSS_SHIFT (0) /* Bits 0-3: Flash CS setup time in terms of clock cycles */
#define QSPI_FLSHCR_TCSS_MASK  (0xf << QSPI_FLSHCR_TCSS_SHIFT)
#  define QSPI_FLSHCR_TCSS(n)  ((n << QSPI_FLSHCR_TCSS_SHIFT) & QSPI_FLSHCR_TCSS_MASK)
                                   /* Bits 4-7: Reserved */
#define QSPI_FLSHCR_TCSH_SHIFT (8) /* Bits 8-11: Flash CS hold time in terms of clock cycles */
#define QSPI_FLSHCR_TCSH_MASK  (0xf << QSPI_FLSHCR_TCSH_SHIFT)
#  define QSPI_FLSHCR_TCSH(n)  ((n << QSPI_FLSHCR_TCSH_SHIFT) & QSPI_FLSHCR_TCSH_MASK)
                                   /* Bits 12-15: Reserved */
#define QSPI_FLSHCR_TDH_SHIFT (16) /* Bits 16-17: Serial flash data in hold time */
#define QSPI_FLSHCR_TDH_MASK  (0x3 << QSPI_FLSHCR_TDH_SHIFT)
#  define QSPI_FLSHCR_TDH(n)  ((n << QSPI_FLSHCR_TDH_SHIFT) & QSPI_FLSHCR_TDH_MASK)
#  define QSPI_FLSHCR_TDH_0   (0  << QSPI_FLSHCR_TDH_SHIFT) /* Data aligned with posedge of
                                                             * Internal reference clock of QuadSPI */
#  define QSPI_FLSHCR_TDH_1   (1  << QSPI_FLSHCR_TDH_SHIFT) /* Data aligned with 2x serial flash
                                                             * half clock */
#  define QSPI_FLSHCR_TDH_2   (2  << QSPI_FLSHCR_TDH_SHIFT) /* Data aligned with 4x serial flash
                                                             * half clock */

                                   /* Bits 18-31: Reserved */

/* QSPI Buffer0 Configuration Register */

#define QSPI_BUF0CR_MSTRID_SHIFT (0) /* Bits 0-3: Master ID */
#define QSPI_BUF0CR_MSTRID_MASK  (0xf << QSPI_BUF0CR_MSTRID_SHIFT)
#  define QSPI_BUF0CR_MSTRID(n)  ((n << QSPI_BUF0CR_MSTRID_SHIFT) & QSPI_BUF0CR_MSTRID_MASK)
                                     /* Bits 4-7: Reserved */
#define QSPI_BUF0CR_ADATSZ_SHIFT (8) /* Bits 8-14: AHB data transfer size */
#define QSPI_BUF0CR_ADATSZ_MASK  (0x7f << QSPI_BUF0CR_ADATSZ_SHIFT)
#  define QSPI_BUF0CR_ADATSZ(n)  ((n << QSPI_BUF0CR_ADATSZ_SHIFT) & QSPI_BUF0CR_ADATSZ_MASK)
                                     /* Bits 15-30: Reserved */
#define QSPI_BUF0CR_HP_EN  (1 << 31) /* Bit 31: High Priority Enable */

/* QSPI Buffer1 Configuration Register */

#define QSPI_BUF1CR_MSTRID_SHIFT (0) /* Bits 0-3: Master ID */
#define QSPI_BUF1CR_MSTRID_MASK  (0xf << QSPI_BUF1CR_MSTRID_SHIFT)
#  define QSPI_BUF1CR_MSTRID(n)  ((n << QSPI_BUF1CR_MSTRID_SHIFT) & QSPI_BUF1CR_MSTRID_MASK)
                                     /* Bits 4-7: Reserved */
#define QSPI_BUF1CR_ADATSZ_SHIFT (8) /* Bits 8-14: AHB data transfer size */
#define QSPI_BUF1CR_ADATSZ_MASK  (0x7f << QSPI_BUF1CR_ADATSZ_SHIFT)
#  define QSPI_BUF1CR_ADATSZ(n)  ((n << QSPI_BUF1CR_ADATSZ_SHIFT) & QSPI_BUF1CR_ADATSZ_MASK)
                                     /* Bits 15-31: Reserved */

/* QSPI Buffer2 Configuration Register */

#define QSPI_BUF2CR_MSTRID_SHIFT (0) /* Bits 0-3: Master ID */
#define QSPI_BUF2CR_MSTRID_MASK  (0xf << QSPI_BUF2CR_MSTRID_SHIFT)
#  define QSPI_BUF2CR_MSTRID(n)  ((n << QSPI_BUF2CR_MSTRID_SHIFT) & QSPI_BUF2CR_MSTRID_MASK)
                                     /* Bits 4-7: Reserved */
#define QSPI_BUF2CR_ADATSZ_SHIFT (8) /* Bits 8-14: AHB data transfer size */
#define QSPI_BUF2CR_ADATSZ_MASK  (0x7f << QSPI_BUF2CR_ADATSZ_SHIFT)
#  define QSPI_BUF2CR_ADATSZ(n)  ((n << QSPI_BUF2CR_ADATSZ_SHIFT) & QSPI_BUF2CR_ADATSZ_MASK)
                                     /* Bits 15-31: Reserved */

/* QSPI Buffer3 Configuration Register */

#define QSPI_BUF3CR_MSTRID_SHIFT (0) /* Bits 0-3: Master ID */
#define QSPI_BUF3CR_MSTRID_MASK  (0xf << QSPI_BUF3CR_MSTRID_SHIFT)
#  define QSPI_BUF3CR_MSTRID(n)  ((n << QSPI_BUF3CR_MSTRID_SHIFT) & QSPI_BUF3CR_MSTRID_MASK)
                                     /* Bits 4-7: Reserved */
#define QSPI_BUF3CR_ADATSZ_SHIFT (8) /* Bits 8-14: AHB data transfer size */
#define QSPI_BUF3CR_ADATSZ_MASK  (0x7f << QSPI_BUF3CR_ADATSZ_SHIFT)
#  define QSPI_BUF3CR_ADATSZ(n)  ((n << QSPI_BUF3CR_ADATSZ_SHIFT) & QSPI_BUF3CR_ADATSZ_MASK)
                                     /* Bits 15-30: Reserved */
#define QSPI_BUF3CR_ALLMST (1 << 31) /* Bit 31: All master enable */

/* QSPI Buffer Generic Configuration Register */

/* Bits 0-11: Reserved */
#define QSPI_BFGENCR_SEQID_SHIFT (12) /* Bits 12-15: Points to a sequence in the Look-up-table */
#define QSPI_BFGENCR_SEQID_MASK  (0xf << QSPI_BFGENCR_SEQID_SHIFT)
#  define QSPI_BFGENCR_SEQID(n)  ((n << QSPI_BFGENCR_SEQID_SHIFT) & QSPI_BFGENCR_SEQID_MASK)
#define QSPI_BFGENCR_PAR_EN (1 << 16) /* Bit 16: When set, a transaction to two serial flash
                                       * devices is triggered in parallel mode */
                                      /* Bits 17-31: Reserved */

/* QSPI SOC Configuration Register */

#define QSPI_SOCCR_QSPISRC_SHIFT (0)    /* Bits 0-2: QSPI clock source select */
#define QSPI_SOCCR_QSPISRC_MASK  (0x7 << QSPI_SOCCR_QSPISRC_SHIFT)
#  define QSPI_SOCCR_QSPISRC(n)  ((n << QSPI_SOCCR_QSPISRC_SHIFT) & QSPI_SOCCR_QSPISRC_MASK)
#  define QSPI_SOCCR_QSPISRC_0   (0  << QSPI_SOCCR_QSPISRC_SHIFT) /* Core/system clock */
#  define QSPI_SOCCR_QSPISRC_1   (1  << QSPI_SOCCR_QSPISRC_SHIFT) /* MCGFLL clock */
#  define QSPI_SOCCR_QSPISRC_2   (2  << QSPI_SOCCR_QSPISRC_SHIFT) /* MCGPLL clock */
#  define QSPI_SOCCR_QSPISRC_3   (3  << QSPI_SOCCR_QSPISRC_SHIFT) /* MCGPLL 2x clock (DDR mode) */
#  define QSPI_SOCCR_QSPISRC_4   (4  << QSPI_SOCCR_QSPISRC_SHIFT) /* IRC48M clock */
#  define QSPI_SOCCR_QSPISRC_5   (5  << QSPI_SOCCR_QSPISRC_SHIFT) /* OSCERCLK clock */
#  define QSPI_SOCCR_QSPISRC_6   (6  << QSPI_SOCCR_QSPISRC_SHIFT) /* MCGIRCLK clock */

                                        /* Bits 3-7: Reserved */
#define QSPI_SOCCR_DQSLPEN    (1 << 8)  /* Bit 8:  When this bit is set the internal generated DQS is
                                         * selected and looped back to QuadSPI, without going to DQS
                                         * pad. DQSPADLPEN should be cleared when this bit is set. */
#define QSPI_SOCCR_DQSPADLPEN (1 << 9)  /* Bit 9:  When this bit is set the internal generated DQS
                                         * will be sent to the DQS pad first and then looped back to
                                         * QuadSPI. DQSLPEN should be cleared when this bit is set. */
#define QSPI_SOCCR_DQSPHASEL_SHIFT (10) /* Bits 10-11: Phase shift for internal DQS generation.
                                         * These bits are always zero in SDR mode. */
#define QSPI_SOCCR_DQSPHASEL_MASK  (0x3 << QSPI_SOCCR_DQSPHASEL_SHIFT)
#  define QSPI_SOCCR_DQSPHASEL(n)  ((n << QSPI_SOCCR_DQSPHASEL_SHIFT) & QSPI_SOCCR_DQSPHASEL_MASK)
#  define QSPI_SOCCR_DQSPHASEL_0   (0  << QSPI_SOCCR_DQSPHASEL_SHIFT) /*   0 degree phase shift */
#  define QSPI_SOCCR_DQSPHASEL_45  (1  << QSPI_SOCCR_DQSPHASEL_SHIFT) /*  45 degree phase shift */
#  define QSPI_SOCCR_DQSPHASEL_90  (2  << QSPI_SOCCR_DQSPHASEL_SHIFT) /*  90 degree phase shift */
#  define QSPI_SOCCR_DQSPHASEL_135 (3  << QSPI_SOCCR_DQSPHASEL_SHIFT) /* 135 degree phase shift */

#define QSPI_SOCCR_DQSINVSEL  (1 << 12) /* Bit 12: Select clock source for internal DQS generation */
#define QSPI_SOCCR_CK2EN      (1 << 13) /* Bit 13: Flash CK2 clock pin enable */
#define QSPI_SOCCR_DIFFCKEN   (1 << 14) /* Bit 14: Differential flash clock pins enable */
#define QSPI_SOCCR_OCTEN      (1 << 15) /* Bit 15: Octal data pins enable */

#define QSPI_SOCCR_DLYTAPSELA_SHIFT (16) /* Bits 16-21: Delay chain tap number for QSPI Port A DQS */
#define QSPI_SOCCR_DLYTAPSELA_MASK  (0x3f << QSPI_SOCCR_DLYTAPSELA_SHIFT)
#  define QSPI_SOCCR_DLYTAPSELA(n)  ((n << QSPI_SOCCR_DLYTAPSELA_SHIFT) & QSPI_SOCCR_DLYTAPSELA_MASK)
#  define QSPI_SOCCR_DLYTAPSELA_0   (0  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  1 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_1   (1  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  2 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_2   (2  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  3 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_3   (3  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  4 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_4   (4  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  5 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_5   (5  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  6 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_6   (6  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  7 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_7   (7  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  8 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_8   (8  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /*  9 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_9   (9  << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 10 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_10  (10 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 11 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_11  (11 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 12 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_12  (12 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 13 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_13  (13 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 14 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_14  (14 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 15 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_15  (15 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 16 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_16  (16 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 17 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_17  (17 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 18 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_18  (18 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 19 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_19  (19 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 20 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_20  (20 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 21 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_21  (21 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 22 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_22  (22 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 23 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_23  (23 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 24 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_24  (24 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 25 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_25  (25 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 26 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_26  (26 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 27 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_27  (27 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 28 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_28  (28 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 29 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_29  (29 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 30 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_30  (30 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 31 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_31  (31 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 32 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_32  (32 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 33 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_33  (33 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 34 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_34  (34 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 35 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_35  (35 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 36 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_36  (36 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 37 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_37  (37 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 38 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_38  (38 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 39 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_39  (39 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 40 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_40  (40 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 41 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_41  (41 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 42 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_42  (42 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 43 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_43  (43 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 44 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_44  (44 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 45 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_45  (45 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 46 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_46  (46 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 47 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_47  (47 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 48 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_48  (48 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 49 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_49  (49 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 50 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_50  (50 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 51 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_51  (51 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 52 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_52  (52 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 53 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_53  (53 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 54 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_54  (54 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 55 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_55  (55 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 56 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_56  (56 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 57 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_57  (57 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 58 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_58  (58 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 59 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_59  (59 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 60 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_60  (60 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 61 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_61  (61 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 62 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_62  (62 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 63 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELA_63  (63 << QSPI_SOCCR_DLYTAPSELA_SHIFT) /* 64 delay chain tap */

/* Bits 22-23: Reserved */
#define QSPI_SOCCR_DLYTAPSELB_SHIFT (24) /* Bits 24-29: Delay chain tap number for QSPI Port B DQS */
#define QSPI_SOCCR_DLYTAPSELB_MASK  (0x3f << QSPI_SOCCR_DLYTAPSELB_SHIFT)
#  define QSPI_SOCCR_DLYTAPSELB(n)  ((n << QSPI_SOCCR_DLYTAPSELB_SHIFT) & QSPI_SOCCR_DLYTAPSELB_MASK)
#  define QSPI_SOCCR_DLYTAPSELB_0   (0  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  1 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_1   (1  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  2 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_2   (2  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  3 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_3   (3  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  4 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_4   (4  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  5 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_5   (5  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  6 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_6   (6  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  7 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_7   (7  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  8 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_8   (8  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /*  9 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_9   (9  << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 10 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_10  (10 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 11 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_11  (11 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 12 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_12  (12 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 13 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_13  (13 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 14 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_14  (14 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 15 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_15  (15 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 16 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_16  (16 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 17 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_17  (17 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 18 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_18  (18 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 19 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_19  (19 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 20 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_20  (20 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 21 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_21  (21 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 22 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_22  (22 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 23 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_23  (23 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 24 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_24  (24 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 25 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_25  (25 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 26 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_26  (26 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 27 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_27  (27 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 28 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_28  (28 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 29 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_29  (29 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 30 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_30  (30 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 31 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_31  (31 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 32 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_32  (32 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 33 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_33  (33 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 34 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_34  (34 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 35 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_35  (35 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 36 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_36  (36 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 37 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_37  (37 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 38 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_38  (38 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 39 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_39  (39 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 40 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_40  (40 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 41 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_41  (41 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 42 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_42  (42 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 43 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_43  (43 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 44 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_44  (44 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 45 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_45  (45 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 46 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_46  (46 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 47 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_47  (47 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 48 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_48  (48 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 49 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_49  (49 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 50 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_50  (50 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 51 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_51  (51 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 52 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_52  (52 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 53 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_53  (53 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 54 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_54  (54 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 55 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_55  (55 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 56 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_56  (56 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 57 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_57  (57 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 58 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_58  (58 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 59 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_59  (59 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 60 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_60  (60 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 61 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_61  (61 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 62 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_62  (62 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 63 delay chain tap */
#  define QSPI_SOCCR_DLYTAPSELB_63  (63 << QSPI_SOCCR_DLYTAPSELB_SHIFT) /* 64 delay chain tap */

                                         /* Bits 30-31: Reserved */

/* QSPI Buffer0 Top Index Register */

                                       /* Bits 0-2: Reserved */
#define QSPI_BUF0IND_TPINDX0_SHIFT (3) /* Bits 3-31: Top index of buffer 0. */
#define QSPI_BUF0IND_TPINDX0_MASK  (0x1fffffff << QSPI_BUF0IND_TPINDX0_SHIFT)
#  define QSPI_BUF0IND_TPINDX0(n)  ((n << QSPI_BUF0IND_TPINDX0_SHIFT) & QSPI_BUF0IND_TPINDX0_MASK)

/* QSPI Buffer1 Top Index Register */

                                       /* Bits 0-2: Reserved */
#define QSPI_BUF1IND_TPINDX1_SHIFT (3) /* Bits 3-31: Top index of buffer 1. */
#define QSPI_BUF1IND_TPINDX1_MASK  (0x1fffffff << QSPI_BUF1IND_TPINDX1_SHIFT)
#  define QSPI_BUF1IND_TPINDX1(n)  ((n << QSPI_BUF1IND_TPINDX1_SHIFT) & QSPI_BUF1IND_TPINDX1_MASK)

/* QSPI Buffer2 Top Index Register */

                                       /* Bits 0-2: Reserved */
#define QSPI_BUF2IND_TPINDX2_SHIFT (3) /* Bits 3-31: Top index of buffer 2. */
#define QSPI_BUF2IND_TPINDX2_MASK  (0x1fffffff << QSPI_BUF2IND_TPINDX2_SHIFT)
#  define QSPI_BUF2IND_TPINDX2(n)  ((n << QSPI_BUF2IND_TPINDX2_SHIFT) & QSPI_BUF2IND_TPINDX2_MASK)

/* QSPI Serial Flash Address Configuration Register */

#define QSPI_SFACR_CAS_SHIFT (0) /* Bits 0-3: Column Address Space */
#define QSPI_SFACR_CAS_MASK  (0xf << QSPI_SFACR_CAS_SHIFT)
#  define QSPI_SFACR_CAS(n)  ((n << QSPI_SFACR_CAS_SHIFT) & QSPI_SFACR_CAS_MASK)
                                 /* Bits 4-15: Reserved */
#define QSPI_SFACR_WA  (1 << 16) /* Bit 16: Word Addressable */
                                 /* Bits 17-31: Reserved */

/* QSPI Sampling Register */

#define QSPI_SMPR_HSENA  (1 << 0)   /* Bit 0:  Half Speed serial flash clock Enable */
#define QSPI_SMPR_HSPHS  (1 << 1)   /* Bit 1:  Half Speed Phase selection for SDR instructions. */
#define QSPI_SMPR_HSDLY  (1 << 2)   /* Bit 2:  Half Speed Delay selection for SDR instructions. */
                                    /* Bits 3-4: Reserved */
#define QSPI_SMPR_FSPHS  (1 << 5)   /* Bit 5:  Full Speed Phase selection for SDR instructions. */
#define QSPI_SMPR_FSDLY  (1 << 6)   /* Bit 6:  Full Speed Delay selection for SDR instructions.
                                     * Select the delay with respect to the reference edge for the
                                     * sample point valid for full speed commands. */
                                    /* Bits 7-15: Reserved */
#define QSPI_SMPR_DDRSMP_SHIFT (16) /* Bits 16-18: DDR Sampling point */
#define QSPI_SMPR_DDRSMP_MASK  (0x7 << QSPI_SMPR_DDRSMP_SHIFT)
#  define QSPI_SMPR_DDRSMP(n)  ((n << QSPI_SMPR_DDRSMP_SHIFT) & QSPI_SMPR_DDRSMP_MASK)
                                    /* Bits 19-31: Reserved */

/* QSPI RX Buffer Status Register */

                                   /* Bits 0-7: Reserved */
#define QSPI_RBSR_RDBFL_SHIFT (8)  /* Bits 8-12: RX Buffer Fill Level */
#define QSPI_RBSR_RDBFL_MASK  (0x1f << QSPI_RBSR_RDBFL_SHIFT)
                                   /* Bits 13-15: Reserved */
#define QSPI_RBSR_RDCTR_SHIFT (16) /* Bits 16-31: Read Counter */
#define QSPI_RBSR_RDCTR_MASK  (0xffff << QSPI_RBSR_RDCTR_SHIFT)
                                   /* Bits 17-31: Reserved */

/* QSPI RX Buffer Control Register */

#define QSPI_RBCT_WMRK_SHIFT (0)  /* Bits 0-3: RX Buffer Watermark */
#define QSPI_RBCT_WMRK_MASK  (0xf << QSPI_RBCT_WMRK_SHIFT)
#  define QSPI_RBCT_WMRK(n)  ((n << QSPI_RBCT_WMRK_SHIFT) & QSPI_RBCT_WMRK_MASK)
                                  /* Bits 4-7: Reserved */
#define QSPI_RBCT_RXBRD (1 << 8)  /* Bit 8:  RX Buffer Readout. This field specifies the access
                                   * scheme for the RX Buffer readout. */
                                  /* Bits 9-31: Reserved */

/* QSPI TX Buffer Status Register */

                                   /* Bits 0-7: Reserved */
#define QSPI_TBSR_TRBFL_SHIFT (8)  /* Bits 8-12: TX Buffer Fill Level */
#define QSPI_TBSR_TRBFL_MASK  (0x1f << QSPI_TBSR_TRBFL_SHIFT)
                                   /* Bits 13-15: Reserved */
#define QSPI_TBSR_TRCTR_SHIFT (16) /* Bits 16-31: Transmit Counter */
#define QSPI_TBSR_TRCTR_MASK  (0xffff << QSPI_TBSR_TRCTR_SHIFT)

/* QSPI Tx Buffer Control Register */

#define QSPI_TBCT_WMRK_SHIFT (0) /* Bits 0-3: Determines the watermark for the TX Buffer */
#define QSPI_TBCT_WMRK_MASK  (0xf << QSPI_TBCT_WMRK_SHIFT)
#  define QSPI_TBCT_WMRK(n)  ((n << QSPI_TBCT_WMRK_SHIFT) & QSPI_TBCT_WMRK_MASK)
                                  /* Bits 4-31: Reserved */

/* QSPI Status Register */

#define QSPI_SR_BUSY    (1 << 0)  /* Bit 0:  Module Busy */
#define QSPI_SR_IP_ACC  (1 << 1)  /* Bit 1:  IP Access. Asserted when transaction currently executed
                                   * was initiated by IP bus. */
#define QSPI_SR_AHB_ACC (1 << 2)  /* Bit 2:  AHB Access. Asserted when the transaction currently
                                   * executed was initiated by AHB bus. */
                                  /* Bits 3-4: Reserved */
#define QSPI_SR_AHBGNT  (1 << 5)  /* Bit 5:  AHB Command priority Granted: Asserted when another
                                   * module has been granted priority of AHB Commands against
                                   * IP Commands. */
#define QSPI_SR_AHBTRN  (1 << 6)  /* Bit 6:  AHB Access Transaction pending */
#define QSPI_SR_AHB0NE  (1 << 7)  /* Bit 7:  AHB 0 Buffer Not Empty */
#define QSPI_SR_AHB1NE  (1 << 8)  /* Bit 8:  AHB 1 Buffer Not Empty */
#define QSPI_SR_AHB2NE  (1 << 9)  /* Bit 9:  AHB 2 Buffer Not Empty */
#define QSPI_SR_AHB3NE  (1 << 10) /* Bit 10: AHB 3 Buffer Not Empty */
#define QSPI_SR_AHB0FUL (1 << 11) /* Bit 11: AHB 0 Buffer Full */
#define QSPI_SR_AHB1FUL (1 << 12) /* Bit 12: AHB 1 Buffer Full */
#define QSPI_SR_AHB2FUL (1 << 13) /* Bit 13: AHB 2 Buffer Full */
#define QSPI_SR_AHB3FUL (1 << 14) /* Bit 14: AHB 3 Buffer Full */
                                  /* Bit 15: Reserved */
#define QSPI_SR_RXWE    (1 << 16) /* Bit 16: RX Buffer Watermark Exceeded */
                                  /* Bits 17-18: Reserved */
#define QSPI_SR_RXFULL  (1 << 19) /* Bit 19: RX Buffer Full */
                                  /* Bits 20-22: Reserved */
#define QSPI_SR_RXDMA   (1 << 23) /* Bit 23: RX Buffer DMA. Asserted when RX Buffer read out via DMA
                                   * is active i.e DMA is requested or running. */
#define QSPI_SR_TXEDA   (1 << 24) /* Bit 24: Tx Buffer Enough Data Available */
#define QSPI_SR_TXWA    (1 << 25) /* Bit 25: TX Buffer watermark Available */
#define QSPI_SR_TXDMA   (1 << 26) /* Bit 26: TXDMA */
#define QSPI_SR_TXFULL  (1 << 27) /* Bit 27: TX Buffer Full.
                                   * Asserted when no more data can be stored. */
                                  /* Bit 28: Reserved */
#define QSPI_SR_DLPSMP_SHIFT (29) /* Bits 29-31: Data learning pattern sampling point */
#define QSPI_SR_DLPSMP_MASK  (0x7 << QSPI_SR_DLPSMP_SHIFT)

/* QSPI Flag Register */

#define QSPI_FR_TFF    (1 << 0)  /* Bit 0:  IP Command Transaction Finished Flag */
                                 /* Bits 1-3: Reserved */
#define QSPI_FR_IPGEF  (1 << 4)  /* Bit 4:  IP Command Trigger during AHB Grant Error Flag */
                                 /* Bit 5: Reserved */
#define QSPI_FR_IPIEF  (1 << 6)  /* Bit 6:  IP Command Trigger could not be executed Error Flag */
#define QSPI_FR_IPAEF  (1 << 7)  /* Bit 7:  IP Command Trigger during AHB Access Error Flag */
                                 /* Bits 8-10: Reserved */
#define QSPI_FR_IUEF   (1 << 11) /* Bit 11: IP Command Usage Error Flag */
#define QSPI_FR_ABOF   (1 << 12) /* Bit 12: AHB Buffer Overflow Flag */
#define QSPI_FR_AIBSEF (1 << 13) /* Bit 13: AHB Illegal Burst Size Error Flag */
#define QSPI_FR_AITEF  (1 << 14) /* Bit 14: AHB Illegal transaction error flag */
#define QSPI_FR_ABSEF  (1 << 15) /* Bit 15: AHB Sequence Error Flag */
#define QSPI_FR_RBDF   (1 << 16) /* Bit 16: RX Buffer Drain Flag */
#define QSPI_FR_RBOF   (1 << 17) /* Bit 17: RX Buffer Overflow Flag */
                                 /* Bits 18-22: Reserved */
#define QSPI_FR_ILLINE (1 << 23) /* Bit 23: Illegal Instruction Error Flag */
                                 /* Bits 24-25: Reserved */
#define QSPI_FR_TBUF   (1 << 26) /* Bit 26: TX Buffer Underrun Flag */
#define QSPI_FR_TBFF   (1 << 27) /* Bit 27: TX Buffer Fill Flag */
                                 /* Bits 28-30: Reserved */
#define QSPI_FR_DLPFF  (1 << 31) /* Bit 31: Data Learning Pattern Failure Flag */

/* QSPI Interrupt and DMA Request Select and Enable Register */

#define QSPI_RSER_TFIE    (1 << 0)  /* Bit 0:  Transaction Finished Interrupt Enable */
                                    /* Bits 1-3: Reserved */
#define QSPI_RSER_IPGEIE  (1 << 4)  /* Bit 4:  IP Command Trigger during AHB Grant
                                     * Error Interrupt Enable */
                                    /* Bit 5: Reserved */
#define QSPI_RSER_IPIEIE  (1 << 6)  /* Bit 6:  IP Command Trigger during IP Access
                                     * Error Interrupt Enable */
#define QSPI_RSER_IPAEIE  (1 << 7)  /* Bit 7:  IP Command Trigger during AHB Access
                                     * Error Interrupt Enable */
                                    /* Bits 8-10: Reserved */
#define QSPI_RSER_IUEIE   (1 << 11) /* Bit 11: IP Command Usage Error Interrupt Enable */
#define QSPI_RSER_ABOIE   (1 << 12) /* Bit 12: AHB Buffer Overflow Interrupt Enable */
#define QSPI_RSER_AIBSIE  (1 << 13) /* Bit 13: AHB Illegal Burst Size Interrupt Enable */
#define QSPI_RSER_AITIE   (1 << 14) /* Bit 14: AHB Illegal Transaction Interrupt Enable. */
#define QSPI_RSER_ABSEIE  (1 << 15) /* Bit 15: AHB Sequence Error Interrupt Enable:
                                     * Triggered by ABSEF flags of QSPI_FR */
#define QSPI_RSER_RBDIE   (1 << 16) /* Bit 16: RX Buffer Drain Interrupt Enable:
                                     * Enables generation of IRQ requests for RX Buffer Drain */
#define QSPI_RSER_RBOIE   (1 << 17) /* Bit 17: RX Buffer Overflow Interrupt Enable */
                                    /* Bits 18-20: Reserved */
#define QSPI_RSER_RBDDE   (1 << 21) /* Bit 21: RX Buffer Drain DMA Enable:
                                     * Enables generation of DMA requests for RX Buffer Drain */
                                    /* Bit 22: Reserved */
#define QSPI_RSER_ILLINIE (1 << 23) /* Bit 23: Illegal Instruction Error Interrupt Enable.
                                     * Triggered by ILLINE flag in QSPI_FR */
                                    /* Bit 24: Reserved */
#define QSPI_RSER_TBFDE   (1 << 25) /* Bit 25: TX Buffer Fill DMA Enable */
#define QSPI_RSER_TBUIE   (1 << 26) /* Bit 26: TX Buffer Underrun Interrupt Enable */
#define QSPI_RSER_TBFIE   (1 << 27) /* Bit 27: TX Buffer Fill Interrupt Enable */
                                    /* Bits 28-30: Reserved */
#define QSPI_RSER_DLPFIE  (1 << 31) /* Bit 31: Data Learning Pattern Failure Interrupt enable.
                                     * Triggered by DLPFF flag in QSPI_FR register */

/* QSPI Sequence Suspend Status Register */

#define QSPI_SPNDST_SUSPND (1 << 0)  /* Bit 0:  When set, it signifies that a sequence
                                      * is in suspended state
                                      */
                                     /* Bits 1-5: Reserved */
#define QSPI_SPNDST_SPDBUF_SHIFT (6) /* Bits 6-7: Suspended Buffer: Provides the suspended buffer
                                      * number. Valid only when SUSPND is set to 1 */
#define QSPI_SPNDST_SPDBUF_MASK  (0x3 << QSPI_SPNDST_SPDBUF_SHIFT)
                                     /* Bit 8: Reserved */
#define QSPI_SPNDST_DATLFT_SHIFT (9) /* Bits 9-14: Data left: Provides information about the amount
                                      * of data left to be read in the suspended sequence */
#define QSPI_SPNDST_DATLFT_MASK  (0x3f << QSPI_SPNDST_DATLFT_SHIFT)
                                     /* Bits 15-31: Reserved */

/* QSPI Sequence Pointer Clear Register */

#define QSPI_SPTRCLR_BFPTRC (1 << 0)  /* Bit 0:  Buffer Pointer Clear: 1: Clears the sequence pointer
                                       * for AHB accesses as defined in QuadSPI_BFGENCR */
                                      /* Bits 1-7: Reserved */
#define QSPI_SPTRCLR_IPPTRC (1 << 8)  /* Bit 8:  IP Pointer Clear: 1: Clears the sequence pointer
                                       * for IP accesses as defined in QuadSPI_IPCR.
                                       * This is a self-clearing field */
                                      /* Bits 9-31: Reserved */

/* QSPI Serial Flash A1 Top Address */

                                      /* Bits 0-9: Reserved */
#define QSPI_SFA1AD_TPADA1_SHIFT (10) /* Bits 10-31: Top address for Serial Flash A1.
                                       * In effect, TPADxx is the first location of the next memory. */
#define QSPI_SFA1AD_TPADA1_MASK  (0x3fffff << QSPI_SFA1AD_TPADA1_SHIFT)
#  define QSPI_SFA1AD_TPADA1(n)  ((n << QSPI_SFA1AD_TPADA1_SHIFT) & QSPI_SFA1AD_TPADA1_MASK)

/* QSPI Serial Flash A2 Top Address */

                                      /* Bits 0-9: Reserved */
#define QSPI_SFA2AD_TPADA2_SHIFT (10) /* Bits 10-31: Top address for Serial Flash A2.
                                       * In effect, TPxxAD is the first location of the next memory. */
#define QSPI_SFA2AD_TPADA2_MASK  (0x3fffff << QSPI_SFA2AD_TPADA2_SHIFT)
#  define QSPI_SFA2AD_TPADA2(n)  ((n << QSPI_SFA2AD_TPADA2_SHIFT) & QSPI_SFA2AD_TPADA2_MASK)

/* QSPI Serial Flash B1 Top Address */

                                      /* Bits 0-9: Reserved */
#define QSPI_SFB1AD_TPADB1_SHIFT (10) /* Bits 10-31: Top address for Serial Flash B1. In effect,
                                       * TPxxAD is the first location of the next memory. */
#define QSPI_SFB1AD_TPADB1_MASK  (0x3fffff << QSPI_SFB1AD_TPADB1_SHIFT)
#  define QSPI_SFB1AD_TPADB1(n)  ((n << QSPI_SFB1AD_TPADB1_SHIFT) & QSPI_SFB1AD_TPADB1_MASK)

/* QSPI Serial Flash B2 Top Address */

                                      /* Bits 0-9: Reserved */
#define QSPI_SFB2AD_TPADB2_SHIFT (10) /* Bits 10-31: Top address for Serial Flash B2. In effect,
                                       * TPxxAD is the first location of the next memory. */
#define QSPI_SFB2AD_TPADB2_MASK  (0x3fffff << QSPI_SFB2AD_TPADB2_SHIFT)
#  define QSPI_SFB2AD_TPADB2(n)  ((n << QSPI_SFB2AD_TPADB2_SHIFT) & QSPI_SFB2AD_TPADB2_MASK)

/* QSPI LUT Lock Configuration Register */

#define QSPI_LCKCR_LOCK   (1 << 0)  /* Bit 0:  Locks the LUT when the following conditions are met:
                                     * 1. This register is written just after the LUT Key Register
                                     * 2. The LUT key register was written with 0x5AF05AF0 key */
#define QSPI_LCKCR_UNLOCK (1 << 1)  /* Bit 1:  Unlocks the LUT when the following conditions are met:
                                     * 1. This register is written just after the LUT Key Register
                                     * 2. The LUT key register was written with 0x5AF05AF0 key */
                                    /* Bits 2-31: Reserved */

/* QSPI Look-up Table register */

#define QSPI_LUT_OPRND0_SHIFT (0)  /* Bits 0-7: Operand for INSTR0. */
#define QSPI_LUT_OPRND0_MASK  (0xff << QSPI_LUT_OPRND0_SHIFT)
#  define QSPI_LUT_OPRND0(n)  ((n << QSPI_LUT_OPRND0_SHIFT) & QSPI_LUT_OPRND0_MASK)

#define QSPI_LUT_PAD0_SHIFT (8)    /* Bits 8-9: Pad information for INSTR0. */
#define QSPI_LUT_PAD0_MASK  (0x3 << QSPI_LUT_PAD0_SHIFT)
#  define QSPI_LUT_PAD0(n)  ((n << QSPI_LUT_PAD0_SHIFT) & QSPI_LUT_PAD0_MASK)
#  define QSPI_LUT_PAD0_1   (0  << QSPI_LUT_PAD0_SHIFT) /* 1 Pad */
#  define QSPI_LUT_PAD0_2   (1  << QSPI_LUT_PAD0_SHIFT) /* 2 Pads */
#  define QSPI_LUT_PAD0_4   (2  << QSPI_LUT_PAD0_SHIFT) /* 4 Pads */
#  define QSPI_LUT_PAD0_8   (3  << QSPI_LUT_PAD0_SHIFT) /* 8 Pads */

#define QSPI_LUT_INSTR0_SHIFT (10) /* Bits 10-15: Instruction 0 */
#define QSPI_LUT_INSTR0_MASK  (0x3f << QSPI_LUT_INSTR0_SHIFT)
#  define QSPI_LUT_INSTR0(n)  ((n << QSPI_LUT_INSTR0_SHIFT) & QSPI_LUT_INSTR0_MASK)

#define QSPI_LUT_OPRND1_SHIFT (16) /* Bits 16-23: Operand for INSTR1. */
#define QSPI_LUT_OPRND1_MASK  (0xff << QSPI_LUT_OPRND1_SHIFT)
#  define QSPI_LUT_OPRND1(n)  ((n << QSPI_LUT_OPRND1_SHIFT) & QSPI_LUT_OPRND1_MASK)

#define QSPI_LUT_PAD1_SHIFT (24)   /* Bits 24-25: Pad information for INSTR1. */
#define QSPI_LUT_PAD1_MASK  (0x3 << QSPI_LUT_PAD1_SHIFT)
#  define QSPI_LUT_PAD1(n)  ((n << QSPI_LUT_PAD1_SHIFT) & QSPI_LUT_PAD1_MASK)
#  define QSPI_LUT_PAD1_1   (0  << QSPI_LUT_PAD1_SHIFT) /* 1 Pad */
#  define QSPI_LUT_PAD1_2   (1  << QSPI_LUT_PAD1_SHIFT) /* 2 Pads */
#  define QSPI_LUT_PAD1_4   (2  << QSPI_LUT_PAD1_SHIFT) /* 4 Pads */
#  define QSPI_LUT_PAD1_8   (3  << QSPI_LUT_PAD1_SHIFT) /* 8 Pads */

#define QSPI_LUT_INSTR1_SHIFT (26) /* Bits 26-31: Instruction 1 */
#define QSPI_LUT_INSTR1_MASK  (0x3f << QSPI_LUT_INSTR1_SHIFT)
#  define QSPI_LUT_INSTR1(n)  ((n << QSPI_LUT_INSTR1_SHIFT) & QSPI_LUT_INSTR1_MASK)

/* LUT Instruction Set */

#define QSPI_INSTR_STOP       0x00
#define QSPI_INSTR_CMD        0x01
#define QSPI_INSTR_ADDR       0x02
#define QSPI_INSTR_DUMMY      0x03
#define QSPI_INSTR_MODE       0x04
#define QSPI_INSTR_MODE2      0x05
#define QSPI_INSTR_MODE4      0x06
#define QSPI_INSTR_READ       0x07
#define QSPI_INSTR_WRITE      0x08
#define QSPI_INSTR_JMP_ON_CS  0x09
#define QSPI_INSTR_ADDR_DDR   0x0a
#define QSPI_INSTR_MODE_DDR   0x0b
#define QSPI_INSTR_MODE2_DDR  0x0c
#define QSPI_INSTR_MODE4_DDR  0x0d
#define QSPI_INSTR_READ_DDR   0x0e
#define QSPI_INSTR_WRITE_DDR  0x0f
#define QSPI_INSTR_DATA_LEARN 0x10
#define QSPI_INSTR_CMD_DDR    0x11
#define QSPI_INSTR_CADDR      0x12
#define QSPI_INSTR_CADDR_DDR  0x13

#endif /* __ARCH_ARM_SRC_KINETIS_HARDWARE_KINETIS_QSPI_H */
