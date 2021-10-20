/*
 * Example code for timer setup in kernel
 *
 */


#include<linux/kernel.h>
//#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/timer.h>
#include<linux/jiffies.h>


#define TIMER_VAL 10000


static struct timer_list test_timer;
static unsigned int time_cnt = 0;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev test_cdev;


static int __init test_driver_init(void);
static void __exit test_driver_exit(void);


/*Driver functions*/

static int test_open(struct inode *inode, struct file *file);
static int test_release(struct inode *inode, struct file *file);

static ssize_t test_read(struct file *filep, char __user *buff, size_t len, loff_t *offset);
static ssize_t test_write(struct file *filep, const char *buff, size_t line, loff_t *offset);

static struct file_operations fops = 
{
	.owner 	= THIS_MODULE,
	.read 	= test_read,
	.write 	= test_write,
	.open 	= test_open,
        .release= test_release,	

};

/*Timer callback*/

void timer_test_cback(struct timer_list *data) 
{
	pr_info("Timer callback function called [%d]\n", time_cnt++);
	mod_timer(&test_timer, jiffies + msecs_to_jiffies(TIMER_VAL));
}

static int test_open(struct inode *inode, struct file *file) {
	pr_info("Timer Device File opened...!\n");
	return 0;
}

static int test_release(struct inode *inode, struct file *file){
	pr_info("Timer Device File closed...!\n");
	return 0;
}


static ssize_t test_read(struct file *filep, char __user *buff, size_t len, loff_t *offset){
	pr_info("Read function\n");
	return 0;
}
static ssize_t test_write(struct file *filep, const char *buff, size_t line, loff_t *offset){
	pr_info("Write function\n");
	return 0;
}

static int __init test_driver_init(void){
	/*Alloc major number*/
	if((alloc_chrdev_region(&dev, 0, 1, "test_timer")) < 0) {
		pr_info("Cannot allocate major number\n");
		return -1;
	}
	pr_info("Major = %d Minor = %d \n", MAJOR(dev), MINOR(dev));
	/*Create cdev structure */
	cdev_init(&test_cdev, &fops);
	/* Add charecter driver */
	if((cdev_add(&test_cdev, dev, 1)) < 0) {
		pr_err("Cannot add the device to the system");
		goto release_class;
	}
	/*Creating struct class */
	if(dev_class = class_create(THIS_MODULE, "test_class") == NULL) {
		pr_err("Cannot create the struct class\n");
		goto release_device;
	}
	/* Creating Device */
	if((device_create(dev_class, NULL, dev, NULL, "test_device")) == NULL ) {
		pr_err("Cannot create dervice \n");
	}
	/*Setup timer to call timer call back*/
	timer_setup(&test_timer, timer_test_cback, 0);

	/*Setup timer interval*/
	mod_timer(&test_timer, jiffies + msecs_to_jiffies(TIMER_VAL));
	pr_info("Device Driver Insert ... Done\n");
	return 0;

release_device:
	class_destroy(dev_class);
release_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

/*Module exit function*/

static void __exit test_driver_exit(void) {
	del_timer(&test_timer);
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&test_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("device Driver remove done..\n");
}
module_init(test_driver_init);
module_exit(test_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MT robotics");
MODULE_DESCRIPTION("A sample device driver - kernel timer");
MODULE_VERSION("1.0");
