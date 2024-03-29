/***************************************************************************//**
*  \file       driver.c
*
*  \details    Simple Linux device driver (Kernel Thread)
*
*  \author     Tirumala Marri based on Embedtronix
*
*  \Tested with Linux raspberrypi 5.10.17-v7+
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/kthread.h>             //kernel threads
#include <linux/sched.h>               //task_struct 
#include <linux/delay.h>
 
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev tm_cdev;
 
static int __init tm_driver_init(void);
static void __exit tm_driver_exit(void);
 
static struct task_struct *tm_thread;
 
/*
** Function Prototypes
*/
/*************** Driver functions **********************/
static int tm_open(struct inode *inode, struct file *file);
static int tm_release(struct inode *inode, struct file *file);
static ssize_t tm_read(struct file *filp, 
                char __user *buf, size_t len,loff_t * off);
static ssize_t tm_write(struct file *filp, 
                const char *buf, size_t len, loff_t * off);
 /******************************************************/
 
int thread_function(void *pv);
/*
** Thread
*/
int thread_function(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) {
        pr_info("In EmbeTronicX Thread Function %d\n", i++);
        msleep(1000);
    }
    return 0;
}
/*
** File operation sturcture
*/ 
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = tm_read,
        .write          = tm_write,
        .open           = tm_open,
        .release        = tm_release,
};
/*
** This function will be called when we open the Device file
*/  
static int tm_open(struct inode *inode, struct file *file)
{
        pr_info("Device File Opened...!!!\n");
        return 0;
}
/*
** This function will be called when we close the Device file
*/   
static int tm_release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}
/*
** This function will be called when we read the Device file
*/
static ssize_t tm_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
        pr_info("Read function\n");
 
        return 0;
}
/*
** This function will be called when we write the Device file
*/
static ssize_t tm_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Write Function\n");
        return len;
}
/*
** Module Init function
*/  
static int __init tm_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "tm_Dev")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&tm_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&tm_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"tm_class")) == NULL){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"tm_device")) == NULL){
            pr_err("Cannot create the Device \n");
            goto r_device;
        }
 
        tm_thread = kthread_create(thread_function,NULL,"eTx Thread");
        if(tm_thread) {
            wake_up_process(tm_thread);
        } else {
            pr_err("Cannot create kthread\n");
            goto r_device;
        }
#if 0
        /* You can use this method also to create and run the thread */
        tm_thread = kthread_run(thread_function,NULL,"eTx Thread");
        if(tm_thread) {
            pr_info("Kthread Created Successfully...\n");
        } else {
            pr_err("Cannot create kthread\n");
             goto r_device;
        }
#endif
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        cdev_del(&tm_cdev);
        return -1;
}
/*
** Module exit function
*/  
static void __exit tm_driver_exit(void)
{
        kthread_stop(tm_thread);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&tm_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(tm_driver_init);
module_exit(tm_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mtreddygmail.com>");
MODULE_DESCRIPTION("Example driver for  Kernel Thread");
MODULE_VERSION("1.0");
