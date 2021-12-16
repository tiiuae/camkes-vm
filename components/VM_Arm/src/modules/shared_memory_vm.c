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
	{&buff_handle, NULL, -1}
};

/*static int guest_write_address(vm_t *vm, uintptr_t paddr, void *vaddr, size_t size, size_t offset, void *cookie)
{
    printf("INSIDE CALLBACK WRITE\n");
    printf("W - COOKIE: %d \n", *(int *)cookie);
    printf("W - COFFSET: %d \n", offset);
    printf("W - VADDR: %p \n", vaddr);
    printf("W - PADDR: %p \n", paddr);
    printf("W - CSIZE: %d \n", size);

    memcpy(vaddr, cookie + offset, size);
    return 0;
}

//VMM read guest memory
static int guest_read_address(vm_t *vm, uintptr_t paddr, void *vaddr, size_t size, size_t offset, void *cookie)
{
    printf("INSIDE CALLBACK READ\n");
    printf("R - COOKIE: %d \n", *(int *)cookie);
    printf("R - OFFSET: %d \n", offset);
    printf("R - VADDR: %p \n", vaddr);
    printf("R - PADDR: %p \n", paddr);
    printf("R - SIZE: %d \n", size);

    memcpy(cookie + offset, vaddr, size);
    return 0;
}*/

static int consume_callback(vm_t *vm, void *cookie)
{
    consume_connection_event(vm, connections[0].consume_badge, true);
    return 0;
}

static int write_buffer(vm_t *vm, uintptr_t load_addr)
{
	char *value = "test";

	vm_ram_mark_allocated(vm, load_addr, 4);

	// vm_ram_touch(vm, load_addr, len, guest_read_address, (void *)buf);
	// JP- vm_ram_touch(vcpu->vm, 0xF1000000, 4, guest_read_address, &buf);
	clean_vm_ram_touch(vm, load_addr, 4, personalized_vm_guest_ram_write_callback, value); // It will never be a ram region as we allocate out of RAM

    printf("%s: WRITE VALUE: %s \n", linux_image_config.vm_name, value);

    char *ptr = (char *)buff;
    printf("%s: WRITE Buffer: %s \n", linux_image_config.vm_name, *(char *)ptr);

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

	if (!strcmp(linux_image_config.vm_name, "vm0")) { // Sender
        
        //addr_ram = 0x2fffffff;    
        addr_ram = 0xDF000000;

        if (done_emit_underlying) {
		connections[0].emit_fn = done_emit_underlying;
        } else if (ready_emit_underlying) {
            connections[0].emit_fn = ready_emit_underlying;
        } else {
            ZF_LOGF("Could not find emit function");
        }

        cross_vm_connections_init(vm, addr_ram, connections, ARRAY_SIZE(connections));
        
        write_buffer(vm, addr_ram);

        // NEXT: SENDING
        // Send the data
        //p1_out_aadl_event_data_send(dataport, &data, emit);  

        char *ptr = (char *)buff;
        printf("Buffer: %d \n", *(char *)ptr);

        /*seL4_Word paddr = *(seL4_Word *)introspect_data;
        printf("paddr in component 0x%x\n", paddr);*/

        /*char *msg = "test";
        printf("%s: sending %s...\n", linux_image_config.vm_name, msg);
        strncpy((char *)buff, msg, BUFF_READY_IDX - 1);

        buff_release(); // ensure the assignment below occurs after the strcpy above
        ((char *)buff)[BUFF_READY_IDX] = 1;*/

	} else if (!strcmp(linux_image_config.vm_name, "vm1")) { // Receiver

        addr_ram = 0xDF000000;

        connections[0].consume_badge = done_notification_badge();
        int err = register_async_event_handler(connections[0].consume_badge, consume_callback, NULL);
        ZF_LOGF_IF(err, "Failed to register_async_event_handler for init_cross_vm_connections.");

        cross_vm_connections_init(vm, addr_ram, connections, ARRAY_SIZE(connections));    

        int i=0;
        while (i<999999999)
        {
            i++;
        }
            
        
        read_buffer(vm, addr_ram);

        char *ptr = (char *)buff;
        printf("Buffer: %d \n", *(char *)ptr);


        /*while (!((char*)buff)[BUFF_READY_IDX]) {
            buff_acquire(); // ensure buff is read from in each iteration
        }

        printf("%s: received %s\n", linux_image_config.vm_name, (char*)buff);*/

	} else if (!strcmp(linux_image_config.vm_name, "vm2")) {
		addr_ram = 0xDF000000;

        cross_vm_connections_init(vm, addr_ram, connections, ARRAY_SIZE(connections));        

	}
}

DEFINE_MODULE(shared_memory_vm, NULL, init_shared_memory_vm)