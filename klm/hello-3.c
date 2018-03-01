/*  
 *  hello-3.c - The simplest kernel module.
 *   To show MODULE_AUTHOR
 *   MODULE_LICENSE etc
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>
#define DERIVER_AUTHOR  "Tirumala Marri"
#define DRIVER_DESC "A test driver"

static int __init hello_4_init(void)
{
	printk(KERN_ERR "Hello world 3.\n");

	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

static void __exit hello_4_exit(void)
{
	printk(KERN_ERR "Goodbye world 3.\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);

/*
 * Get rid of taint message by adding GPL
 */
MODULE_LICENSE("GPL");

/*
 * author etc
 */
MODULE_AUTHOR(DERIVER_AUTHOR);   /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);    /* What does this module do */

/*  
 *   *  This module uses /dev/testdevice.  The MODULE_SUPPORTED_DEVICE macro might
 *    *  be used in the future to help automatic configuration of modules, but is 
 *     *  currently unused other than for documentation purposes.
 *      */
MODULE_SUPPORTED_DEVICE("testdevice");
