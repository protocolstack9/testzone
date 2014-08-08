#include <linux/module.h>			// module_init
#include <linux/kernel.h>

#include <linux/vmalloc.h>			// vmalloc/vfree

#include <linux/slab.h>				// kmalloc/kfree
#include <linux/types.h>			// u32

#include <linux/utsname.h>			// utsname

#include <linux/kthread.h>			// kthread_run
#include <linux/printk.h>			// pr_debug
#include <asm/sizes.h>				// SZ_1MB

struct task_struct *task_test = NULL;


/* from kernel/lockdep.c */
static void print_kernel_ident_ext(void)
{
	printk("release:  [%s]\n", init_utsname()->release);
	printk("sysname:  [%s]\n", init_utsname()->sysname);
	printk("nodename: [%s]\n", init_utsname()->nodename);
	printk("sysname:  [%.*s]\n", (int)strcspn(init_utsname()->version, " "),
		init_utsname()->version);
	printk("machine:  [%s]\n", init_utsname()->machine);
	printk("domainname:  [%s]\n", init_utsname()->domainname);
	//print_tainted();

	/*
	from include/linux/utsname.h

	struct new_utsname {
		char sysname[__NEW_UTS_LEN + 1];
		char nodename[__NEW_UTS_LEN + 1];
		char release[__NEW_UTS_LEN + 1];
		char version[__NEW_UTS_LEN + 1];
		char machine[__NEW_UTS_LEN + 1];
		char domainname[__NEW_UTS_LEN + 1];
	};

	example:
		release:  [3.4.39+]
		sysname:  [Linux]
		nodename: [NEXELL]
		sysname:  [#15]
		machine:  [armv7l]
		domainname:  [(none)]
	*/
}

static void print_pid_info(void)
{
	struct task_struct *curr = current;

	printk("I'm %s. pid: %d, tgid: %d\n",
		curr->comm, task_pid_nr(curr), task_tgid_nr(curr));
}




/*
	physical kernel memory size : 1G.
	User/Kernel space : 2G/2G Split.

	Memory: 1024MB = 1024MB total
	Memory: 809056k/809056k available, 239520k reserved, 0K highmem
	Virtual kernel memory layout:
		vector  : 0xffff0000 - 0xffff1000   (   4 kB)
		fixmap  : 0xfff00000 - 0xfffe0000   ( 896 kB)
		vmalloc : 0xc0800000 - 0xfee00000   ( 998 MB)		// lowmem 이후 8MB Align.
		lowmem  : 0x80000000 - 0xc0000000   (1024 MB)		// kernel address <-> physical direct-mapping
		pkmap   : 0x7fe00000 - 0x80000000   (   2 MB)
		modules : 0x7f000000 - 0x7fe00000   (  14 MB)
		  .text : 0x80008000 - 0x80781ae4   (7655 kB)
		  .init : 0x80782000 - 0x807b6d40   ( 212 kB)
		  .data : 0x807b8000 - 0x8082cd20   ( 468 kB)
		   .bss : 0x8082cd44 - 0x809f2608   (1815 kB)


	[실행결과]
		# insmod alloc_works.ko

		release:  [3.4.39+]
		sysname:  [Linux]
		nodename: [NEXELL]
		sysname:  [#15]
		machine:  [armv7l]
		domainname:  [(none)]

		 [alloc_init] 
		caller : 
		I'm insmod. pid: 791, tgid: 791
		[do_alloc_test] thread running!
		 callee : 
		I'm kalloc_test. pid: 793, tgid: 793
		kmalloc addr: b1900000
		vmalloc addr: c0c2b000
 */
static int do_alloc_test(void *data)
{
	//int order;
	void *vaddr;

	pr_info("[%s] thread running!\n", __func__);

	pr_info("callee : \n");	/* current->pid */
	print_pid_info();


	/* kmalloc test */
	vaddr = kmalloc(SZ_8M, GFP_KERNEL);
	if (vaddr == NULL) {
		pr_err("\t>>> kmalloc alloc_fail\n");
		return -1;
	}

	pr_info("kmalloc addr: %x\n", (u32)vaddr);

	kfree(vaddr);


	/* vmalloc test */
	vaddr = vmalloc(SZ_1M);
	if (vaddr == NULL) {
		pr_err("\t>>> vmalloc alloc_fail\n");
		return -1;
	}

	pr_info("vmalloc addr: %x\n", (u32)vaddr);

	vfree(vaddr);


	return 0;
}

// TODO:
// symbol name, address 출력
// 다른 kthread api : kthread_stop, ...
// semaphore 사용
// argument 전달 : sys interface 사용, module_param 사용
// get_free_pages,
// Documentation/DMA-API.txt, DMA-API-HOWTO.txt : dma_alloc_coherent, dma_map_single

static int __init alloc_init(void)
{
	print_kernel_ident_ext();
	printk("\n");
	pr_info(" [%s] \n", __func__);

	pr_info("caller : \n");	/* current->pid */
	print_pid_info();

	if (task_test == NULL)
		task_test = kthread_run(do_alloc_test, NULL, "kalloc_test");
	return 0;
}

static void __exit alloc_exit(void)
{
	pr_info(" [%s] \n", __func__);
	return ;
}


MODULE_LICENSE("GPL");
module_init(alloc_init);
module_exit(alloc_exit);
