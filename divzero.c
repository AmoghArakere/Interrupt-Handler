#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "divide_by_zero"
#define IOCTL_CMD _IOR('d', 1, int *)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to handle divide-by-zero exceptions");
MODULE_VERSION("1.0");

static int dev_major;
static struct cdev cdev;

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == IOCTL_CMD) {
        printk(KERN_INFO "Divide-by-zero exception occurred in user mode.\n");
        return 0;
    }
    return -EINVAL;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = device_ioctl,
};

static int __init divide_by_zero_init(void) {
    int result;
    dev_major = register_chrdev(0, DEVICE_NAME, &fops);
    if (dev_major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", dev_major);
        return dev_major;
    }
    printk(KERN_INFO "Divide-by-zero handler module loaded.\n");
    printk(KERN_INFO "I was assigned major number %d. To talk to\n", dev_major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, dev_major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;
    result = cdev_add(&cdev, MKDEV(dev_major, 0), 1);
    if (result) {
        printk(KERN_NOTICE "Error %d adding device\n", result);
        unregister_chrdev(dev_major, DEVICE_NAME);
        return result;
    }

    return 0;
}

static void __exit divide_by_zero_exit(void) {
    cdev_del(&cdev);
    unregister_chrdev(dev_major, DEVICE_NAME);
    printk(KERN_INFO "Divide-by-zero handler module unloaded.\n");
}

module_init(divide_by_zero_init);
module_exit(divide_by_zero_exit);

