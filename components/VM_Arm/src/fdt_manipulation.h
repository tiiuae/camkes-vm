/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

/**
* generate a "memory" node
* @param fdt
* @param base, the base of the memory region
* @param size, the size of the memory region
* @return -1 on error, 0 otherwise
*/
int fdt_generate_memory_node(void *fdt, unsigned long base, size_t size);

/**
* generate a "ramoops" node
* @param fdt
* @param base, the base of the memory region
* @param size, the size of the memory region
* @return -1 on error, 0 otherwise
*/
int fdt_generate_ramoops_node(void *fdt, unsigned long base, size_t size);

/**
* generate a "sel4_tracebuffer" node
* @param fdt
* @param base, the base of the memory region
* @param size, the size of the memory region
* @return -1 on error, 0 otherwise
*/
int fdt_generate_sel4_tracebuffer_node(void *fdt, unsigned long base, size_t size);

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
int fdt_append_chosen_node_with_initrd_info(void *fdt, unsigned long base, size_t size);

/**
* generate a "usb@0,0" sub-node of "pci@0,0"
* TODO: camkes-tool is not able to pass it from .dts file currently.
* This can be removed as soon as camkes-tool is fixed.
* @param fdt
* @return -1 on error, 0 otherwise
*/
int fdt_generate_usb_node(void *fdt);
