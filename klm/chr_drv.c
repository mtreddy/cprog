#include<cdev.h>
#include<device.h>
#include<kernel.h>
#include<linux/fs.h>

#define MAXDEVS	2


static const struct file_operations mychardev_ops = {
	.owner	= THIS_MODULE;
	.open	= mychardev_open;
	.release = mychardev_release;
	.unlocked_ioctl = mycardev_ioctl;
	.read	= mychardev_read;
	.write	= mychardev_write;
};

struct mychar_device_data {
	struct cdev cdev;
};

static int dev_major = 0;

static struct class *mychardev_class = NULL;
