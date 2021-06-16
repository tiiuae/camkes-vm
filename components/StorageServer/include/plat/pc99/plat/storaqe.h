/*
 * Copyright 2019, Dornerworks
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once

#define SATADRIVER_AHCI_ENABLE

#define HARDWARE_SATA_PROVIDES_INTERFACES                                          \
    dataport Buf(8192) mmio;

#define HARDWARE_SATA_INTERFACES                                                   \
    dataport Buf(8192) ahcidriver;

#define HARDWARE_SATA_COMPOSITION                                                  \
    component HWSata HWsata;                                                       \
    connection seL4HardwareMMIO satadrivermmio(from ahcidriver, to HWsata.mmio);

#define HARDWARE_SATA_CONFIG                                                       \
    /* In AHCI mode the PCI device has an associated memory space */               \
    HWsata.mmio_paddr = 0xf7f36000;                                                \
    HWsata.mmio_size = 0x2000;

    
#define PROVIDED_STORAGE_INTERFACES    HARDWARE_SATA_PROVIDES_INTERFACES
#define STORAGE_INTERFACES             HARDWARE_SATA_INTERFACES
#define STORAGE_COMPOSITION            HARDWARE_SATA_COMPOSITION
#define STORAGE_CONFIG                 HARDWARE_SATA_CONFIG
