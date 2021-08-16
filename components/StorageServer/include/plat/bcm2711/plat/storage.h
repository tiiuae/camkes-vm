/*
 * Copyright 2021, Unikie
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once

#define EMULATED_PROVIDES_STORAGE_INTERFACES                                       \
    dataport Buf(16777216) disk;
    
#define EMULATED_STORAGE_ATTRIBUTES
    
#define EMULATED_STORAGE_INTERFACES                                                \
    dataport Buf(16777216) diskdriver;

#define EMULATED_STORAGE_COMPOSITION                                               \
    component Storage stor;                                                        \
    connection seL4SharedData diskdriver_conn(from diskdriver, to stor.disk);
    
#define EMULATED_STORAGE_CONFIG                                                    \
    stor.mmio_paddr = 0x100000000;                                                 \
    stor.mmio_size = 0x1000000;


#define PLAT_PROVIDES_STORAGE_INTERFACES    EMULATED_PROVIDES_STORAGE_INTERFACES
#define PLAT_STORAGE_SERVER_ATTRIBUTES      EMULATED_STORAGE_ATTRIBUTES
#define PLAT_STORAGE_SERVER_INTERFACES      EMULATED_STORAGE_INTERFACES
#define PLAT_STORAGE_COMPOSITION            EMULATED_STORAGE_COMPOSITION
#define PLAT_STORAGE_CONFIG                 EMULATED_STORAGE_CONFIG
