/*
 * Copyright 2021, Unikie
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once

/*
 * StorageServer statuses.
 */ 
enum {
    STORAGESERVER_OK = 0,
    STORAGESERVER_NOT_READY,
    STORAGESERVER_INVALID_CONFIG
}

#define STORAGESERVER_MAX_PARTS_PER_CLIENT 4
#define STORAGESERVER_MAX_DISKS_PER_CLIENT 4
