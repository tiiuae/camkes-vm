/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#pragma once

#define IRQ_SPI_OFFSET 32
#define GIC_IRQ_PHANDLE 0x01

static const int linux_pt_irqs[] = {};

// TODO: define free interrupts somehow, -1 means no free interrupts
static const int free_plat_interrupts[] =  { -1 };
static const char *plat_keep_devices[] = {};
static const char *plat_keep_device_and_disable[] = {};
static const char *plat_keep_device_and_subtree[] = {};
static const char *plat_keep_device_and_subtree_and_disable[] = {};
