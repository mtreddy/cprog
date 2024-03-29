/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>

static int __init hello_2_init(void)
{
	printk(KERN_CRIT "Hello world 2.\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

static void __exit hello_2_exit(void)
{
	printk(KERN_CRIT "Goodbye world 2.\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);
