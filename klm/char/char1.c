#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put user*/

#define MODULE_DESC "Charecter test driver"
#define DEV_NAME  "CDEV"

static int cdev_open(struct inode *inode, struct file *file);
static int cdev_release(struct inode *inode, struct file *file);
static int cdev_read(struct file *filep, char *buffer, size_t length, loff_t *offset);
static int cdev_write(struct file *filep, char *buffer, size_t length, loff_t *offset);

static struct file_operations fops = {
    .read  = cdev_read,
    .write = cdev_write,
    .open  = cdev_open,
    .release = cdev_release,
};

static int major;
static int dev_open = 0;
static char *msg_ptr;
static char msg[80];

int cdev_init_moudle(void) {
    major = register_chrdev( 0, DEV_NAME, &fops);
    if(major < 0) {
        printk(KERN_ALERT " Failed to register cdevice major = %d\n", major);
        return major;
    }
    printk("cdev major=%d\n", major);
    return 0;
}

void cdev_cleanup_module(void) {
    int ret = 0;
    unregister_chrdev(major, DEV_NAME);
    if(ret < 0) {
        printk(KERN_ALERT "Failed to unregister cdev..\n");
    }
}

static int cdev_open(struct inode *inode, struct file *file){
    static int counter = 0;

    if(dev_open)
        return -EBUSY;
    dev_open++;
    sprintf(msg, " called %d times hello world\n", counter);
    msg_ptr = msg;
    try_module_get(THIS_MODULE);
    return 0;
}
static int cdev_release(struct inode *inode, struct file *file){
    dev_open--;
    /*
     * Decriment usage count
     */
    module_put(THIS_MODULE);
    return 0;
}
static ssize_t cdev_read(struct file *filep, char *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    /*Check if end of the message*/
    if(*msg_ptr == 0)
        return 0;

    while(length && *msg_ptr){
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}
static ssize_t cdev_write(struct file *filep, char *buffer, size_t length, loff_t *offset) {
    printk(KERN_INFO "Not implemented yet..\n");
    return 0;
}

module_init(cdev_init_moudle);
module_exit(cdev_cleanup_module);
