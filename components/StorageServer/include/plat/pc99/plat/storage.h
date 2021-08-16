/*
 * Copyright 2019, Dornerworks
 * Copyright 2021, Unikie
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once

#define SATADRIVER_AHCI_ENABLE

#define HARDWARE_SATA_PROVIDES_INTERFACES                                          \
    dataport Buf(8192) mmio;
    
#define HARDWARE_SATA_ATTRIBUTES

#define HARDWARE_SATA_INTERFACES                                                   \
    dataport Buf(8192) ahcidriver;

#define HARDWARE_SATA_COMPOSITION                                                  \
    component HWSata HWsata;                                                       \
    connection seL4HardwareMMIO satadrivermmio(from ahcidriver, to HWsata.mmio);

#define HARDWARE_SATA_CONFIG                                                       \
    /* In AHCI mode the PCI device has an associated memory space */               \
    HWsata.mmio_paddr = 0xf7f36000;                                                \
    HWsata.mmio_size = 0x2000;

    
#define PLAT_PROVIDES_STORAGE_INTERFACES    HARDWARE_SATA_PROVIDES_INTERFACES
#define PLAT_STORAGE_SERVER_ATTRIBUTES      HARDWARE_SATA_ATTRIBUTES
#define PLAT_STORAGE_SERVER_INTERFACES      HARDWARE_SATA_INTERFACES
#define PLAT_STORAGE_COMPOSITION            HARDWARE_SATA_COMPOSITION
#define PLAT_STORAGE_CONFIG                 HARDWARE_SATA_CONFIG
