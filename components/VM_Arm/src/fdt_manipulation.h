/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2023, Technology Innovation Institute
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once


/**
* append variable size property to node
* @param fdt
* @param offset, the node offset
* @param name, the property name
* @param value, the property value
* @param num_cells, the number of cells to append
* @return -1 on error, 0 otherwise
*/
int fdt_appendprop_uint(void *fdt, int offset, const char *name, uint64_t val,
                        int num_cells);

/**
* generate a "memory" node
* @param fdt
* @param base, the base of the memory region
* @param size, the size of the memory region
* @return -1 on error, 0 otherwise
*/
int fdt_generate_memory_node(void *fdt, uintptr_t base, size_t size);

/**
* generate a "chosen" node
* @param fdt
* @param stdout_path, the path of the stdout
* @param bootargs
* @param maxcpus
* @return -1 on error, 0 otherwise
*/
int fdt_generate_chosen_node(void *fdt, const char *stdout_path, const char *bootargs, const unsigned int maxcpus);

/**
* append the chosen node with initrd info
* @param fdt
* @param base, the base of the initrd image
* @param size, the size of the initrd image
* @return -1 on error, 0 otherwise
*/
int fdt_append_chosen_node_with_initrd_info(void *fdt, uintptr_t base, size_t size);
