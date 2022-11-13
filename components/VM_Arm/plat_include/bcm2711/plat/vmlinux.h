/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

/*
 * BCM2711 TRM
 * section 6.3.   GIC-400: SPI IDs start from 32
 * section 6.5.1  
 *                GIC-400 ARM base address: 0x4c0040000
 *                GIC-400 Low-Peripheral mode base address: 0xff840000
 *                GIC-400 is configured with: "NUM_CPUS=4", "NUM_SPIS=192"
 */
#define IRQ_SPI_OFFSET 32
#define GIC_NODE_PATH "/soc/interrupt-controller@40041000"

static const int linux_pt_irqs[] = {};

/*
 * BCM2711 TRM
 * section 6.2.3. ARMC interrupts: Software interrupts 0-7: 8-15
 * section 6.3.   GIC-400 - ARMC peripheral IRQs: 64-79
 * => Software interrupt 0 = 72
 *    Software interrupt 1 = 73
 *    Software interrupt 2 = 74
 *    Software interrupt 3 = 75
 *    Software interrupt 4 = 76
 *    Software interrupt 5 = 77
 *    Software interrupt 6 = 78
 *    Software interrupt 7 = 79
 */

/* 
 * Although using the software interrupts (SGIs?) listed above seem to work,
 * I don't know if using them is the intended use case for this. Any documentation
 * I can find doesn't really elaborate anything on how to use the SGIs.
 * 
 * So, the Ultibo project has done a whole lot on RPi4 support, and a RPi4 SoC
 * definitions can be found here (BCM2711 is based on BCM2838):
 * https://github.com/ultibohub/Core/blob/master/source/rtl/ultibo/core/bcm2838.pas
 * 
 * The last interrupt listed there is the xHCI controller IRQ, IRQ_SPI_OFFSET + 176.
 * Based on that and the fact that "NUM_SPIS" is set to 192, we should have a whole
 * lot of IRQs to use which don't correspond to any HW IRQ, SPI IDs 177->192.
 * Don't know if this is correct either, as the documentation sucks, but this also
 * seems to work.
 */
static const int free_plat_interrupts[] =  { IRQ_SPI_OFFSET + 177,
                                             IRQ_SPI_OFFSET + 178,
                                             IRQ_SPI_OFFSET + 179,
                                             IRQ_SPI_OFFSET + 180,
                                             IRQ_SPI_OFFSET + 181 };
//static const int free_plat_interrupts[] =  { 72, 73, 74, 75, 76, 77, 78, 79 };
static const char *plat_keep_devices[] = {
    "/timer",
    "/soc/interrupt-controller@40041000",
};
static const char *plat_keep_device_and_disable[] = {};
static const char *plat_keep_device_and_subtree[] = {};
static const char *plat_keep_device_and_subtree_and_disable[] = {};
