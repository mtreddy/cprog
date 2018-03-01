/*  
 *  hello-3.c - The simplest kernel module.
 *   To show MODULE_AUTHOR
 *   MODULE_LICENSE etc
 */
#include <linux/moduleparam.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>
#include <linux/stat.h>
#define DERIVER_AUTHOR  "Tirumala Marri"
#define DRIVER_DESC "A test driver"
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DERIVER_AUTHOR);   /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);    /* What does this module do */

static short int myshort = 1;
static int myint = 400;
static char *mystr = "Hello";

module_param(myshort, short, S_IRUGO);// ,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) ;
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "A integer");
module_param(mystr, charp, 0000 );
MODULE_PARM_DESC(mystr, "A charecter string");

static int __init hello_4_init(void)
{
	printk(KERN_INFO "Hello world 4.\n");

    printk(KERN_INFO" myshort %d\n", myshort);
    printk(KERN_INFO" myint is %d\n", myint);
    printk(KERN_INFO" mystr is %s\n", mystr);
	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

static void __exit hello_4_exit(void)
{
	printk(KERN_INFO "Goodbye world 4.\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);


/*  
 *   *  This module uses /dev/testdevice.  The MODULE_SUPPORTED_DEVICE macro might
 *    *  be used in the future to help automatic configuration of modules, but is 
 *     *  currently unused other than for documentation purposes.
 *      */
MODULE_SUPPORTED_DEVICE("testdevice");
