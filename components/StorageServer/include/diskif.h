/*
 * Copyright 2021, Unikie
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once

#define DISK_BLK_SIZE     512

enum {
    DISK_OK,
    DISK_DRIVE_NOT_FOUND,
    DISK_INVALID_POSITION,
    DISK_INVALID_TYPE,
    DISK_INVALID_DIRECTION,
    DISK_INVALID_PTR
};

typedef struct partition_table {
    uint8_t boot;
    uint8_t head;
    uint16_t sec_cyl;
    uint8_t sys_id;
    uint8_t end_head;
    uint16_t end_sec_cyl;
    uint32_t start_lba;
    uint32_t num_sectors;
} partition_table_t;

int disk_get_partition_tables(uint8_t drive, partition_table_t *partition_tables, uint8_t *part_data);
int disk_read_sectors(uint8_t drive, uint16_t numsects, uint32_t lba, uint8_t *buf);
int disk_write_sectors(uint8_t drive, uint16_t numsects, uint32_t lba, uint8_t *buf);
int disk_init(ps_io_ops_t *io_ops, void *config);
