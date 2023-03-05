/*
 * Copyright 2023, Technology Innovation Institute
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <camkes.h>

#include <vm_image.h>

/*- if 'images' in configuration[me.name].keys() -*/
    /*- for img in configuration[me.name].get('images').split() -*/
        /*- set id, filename, type, addr, max_size = img.split(':') -*/
USED SECTION("_vm_images")
vm_image_t vm_image_/*? id ?*/ = {
    .id = "/*? id ?*/",
    .filename = "/*? filename ?*/",
        /*- if type == 'raw' -*/
    .type = VM_IMAGE_RAW,
        /*- elif type == 'elf' -*/
    .type = VM_IMAGE_ELF,
        /*- else -*/
            /*? raise(TemplateError('Invalid image type %s' % (type))) ?*/
        /*- endif -*/
    .addr = /*? addr ?*/,
    .max_size = /*? max_size ?*/,
};
    /*- endfor -*/
/*- endif -*/
