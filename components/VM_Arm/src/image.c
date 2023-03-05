/*
 * Copyright 2023, Technology Innovation Institute
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <vm_image.h>

/* Force the _vm_images section to be created even if no images are defined. */
static USED SECTION("_vm_images") struct {} dummy_vm_image;

extern vm_image_t __start__vm_images[];
extern vm_image_t __stop__vm_images[];

int load_images(vm_t *vm)
{
    for (vm_image_t *image = __start__vm_images;
        image < __stop__vm_images; image++) {
        ZF_LOGI("Loading VM image '%s'", image->id);

        int err = vm_load_guest_module(vm, image->filename, image->addr, 0,
                                       &image->guest_image);
        if (err) {
            ZF_LOGE("Loading VM image '%s' failed (%d)", image->id, err);
            return err;
        }

        if (image->guest_image.size > image->max_size) {
            ZF_LOGE("VM image '%s' size %zu exceeds maximum %zu", image->id,
                    image->guest_image.size, image->max_size);
            return -1;
        }
    }

    return 0;
}
