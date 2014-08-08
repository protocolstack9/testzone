#include <linux/module.h>
#include <linux/kernel.h>

static int __init basic_init(void)
{
	printk(KERN_INFO " [%s] \n", __func__);
	return 0;
}

static void __exit basic_exit(void)
{
	printk(KERN_INFO " [%s] \n", __func__);
	return ;
}


MODULE_LICENSE("GPL");
module_init(basic_init);
module_exit(basic_exit);
