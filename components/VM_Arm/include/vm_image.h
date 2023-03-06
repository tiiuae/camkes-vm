/*
 * Copyright 2023, Technology Innovation Institute
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <camkes.h>

#include <sel4vmmplatsupport/guest_image.h>

typedef enum {
    VM_IMAGE_RAW,
    VM_IMAGE_ELF,
} vm_image_type_t;

typedef struct {
    char *id;
    char *filename;
    vm_image_type_t type;
    uintptr_t addr;
    size_t max_size;
    guest_image_t guest_image;
} vm_image_t;

int load_linux(vm_t *);
