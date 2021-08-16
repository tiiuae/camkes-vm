/*
 * Copyright 2021, Unikie
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#define VM_INIT_STORAGE()                            \
    has mutex virtio_blk_mutex;                      \
    uses StorageServerInterface storageserver_iface;

#define STORAGE_COMPOSITION_DEF()                               \
    component StorageServer storageserver;                      \
    connection seL4RPCCall storageserver_serial(from storageserver.putchar, to serial.processed_putchar);

/* Convenience wrapper for connecting VMs to the StorageServer component
 * num: vm instance number
*/
#define VM_STORAGE_CONNECTIONS(num)                                                     \
    connection seL4StorageServer vm##numstorageservercon(from vm##num.storageserver_iface, to storageserver.client);

/* Convenience wrapper for configuring the StorageServer
 */
#define VM_STORAGE_CONFIG()                                                                        \
    storageserver.simple = true;                /* Links component to component.simple.c */               \
    storageserver.cnode_size_bits = 16;         /* Changes cnode size from default 12 to 16 */            \
    storageserver.simple_untyped23_pool = 2;    /* Creates 2 untyped pools of size 2^23 */                \
    storageserver.heap_size = 0x30000;          /* RAM allocation available to storageserver component */    \
    storageserver.dma_pool = 0x20000;                                                                     \
    storageserver.putchar_attributes = 0;
