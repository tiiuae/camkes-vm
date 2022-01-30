/*
 * Copyright 2021, SSRC, TII
 *
 */

#include <autoconf.h>
#include <camkes.h>
#include <vmlinux.h>
#include <sel4vm/guest_vm.h>
#include <sel4vm/guest_ram.h>

#include <sel4vmmplatsupport/drivers/cross_vm_connection.h>
#include <sel4vmmplatsupport/drivers/pci_helper.h>
#include <pci/helper.h>

#include <signal.h>

#ifdef CONFIG_PLAT_QEMU_ARM_VIRT
#define CONNECTION_BASE_ADDRESS 0xDF000000
#else
#define CONNECTION_BASE_ADDRESS 0x3F000000
#endif

#define BUFF_READY_IDX 20

//example going from linux to native component
static void sys_ipa_to_pa(void *cookie)
{
    printf("address from linux is %x\n", *(seL4_Word *)buff);

    ready_emit();
}

// these are defined in the dataport's glue code
extern dataport_caps_handle_t buff_handle;

void done_emit_underlying(void); 

static struct camkes_crossvm_connection connections[] = {
	{&buff_handle, NULL, -1, NULL}
};

static int consume_callback(vm_t *vm, void *cookie)
{
    consume_connection_event(vm, connections[0].consume_badge, true);
    return 0;
}

static int write_buffer(vm_t *vm, uintptr_t load_addr)
{
	char *value = "test";

	vm_ram_mark_allocated(vm, load_addr, 4);

	clean_vm_ram_touch(vm, load_addr, 4, personalized_vm_guest_ram_write_callback, value); // It will never be a ram region as we allocate out of RAM

    printf("%s: WRITE VALUE: %s \n", linux_image_config.vm_name, value);

    char *ptr = (char *)buff;
    printf("%s: WRITE Buffer: %s \n", linux_image_config.vm_name, *ptr);

    return 0;
}

static int read_buffer(vm_t *vm, uintptr_t load_addr)
{
    char *value_test;

    vm_ram_mark_allocated(vm, load_addr, 4);

    clean_vm_ram_touch(vm, load_addr, 4, personalized_vm_guest_ram_read_callback, &value_test);

    printf("%s: READ VALUE: %s \n", linux_image_config.vm_name, value_test);

    return 0;
}

void done_emit_underlying(void) WEAK;
void ready_emit_underlying(void) WEAK;
extern seL4_Word done_notification_badge(void);
void init_shared_memory_vm(vm_t *vm, void *cookie)
{
	uintptr_t addr_ram;

	if (!strcmp(linux_image_config.vm_name, "vm0")) { 
        
        if (done_emit_underlying) {
		connections[0].emit_fn = done_emit_underlying;
        } else if (ready_emit_underlying) {
            connections[0].emit_fn = ready_emit_underlying;
        } else {
            ZF_LOGF("Could not find emit function");
        }

        cross_vm_connections_init(vm, CONNECTION_BASE_ADDRESS, connections, ARRAY_SIZE(connections));
        
        write_buffer(vm, CONNECTION_BASE_ADDRESS);

        char *ptr = (char *)buff;
        printf("Buffer: %p - 0x%x\n", ptr, *ptr);

	} else if (!strcmp(linux_image_config.vm_name, "vm1")) { 
        //return;

        connections[0].consume_badge = done_notification_badge();
        int err = register_async_event_handler(connections[0].consume_badge, consume_callback, NULL);
        ZF_LOGF_IF(err, "Failed to register_async_event_handler for init_cross_vm_connections.");

        cross_vm_connections_init(vm, CONNECTION_BASE_ADDRESS, connections, ARRAY_SIZE(connections));    

        int i=0;
        while (i<999999999)
        {
            i++;
        }
            
        
        read_buffer(vm, CONNECTION_BASE_ADDRESS);

        char *ptr = (char *)buff;
        printf("Buffer: %p - 0x%x\n", ptr, *ptr);

	}
}

DEFINE_MODULE(shared_memory_vm, NULL, init_shared_memory_vm)