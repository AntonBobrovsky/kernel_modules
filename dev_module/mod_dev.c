#include "../include/common.h"

static int device_open(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_release(struct inode *, struct file *);

#define DEVICE_NAME "hello_device"
#define DEVICE_CLASS "test_class"
#define BUF_LEN 80

static int Major; /* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open? */

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};

/* This function is called when the module is loaded */
static int __init mod_init(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
	}

    printk( "Test module is loaded!\n" );
    printk(KERN_INFO "I was assigned major number %d.\n", Major);
    printk( "Please, create a dev file with 'mknod /dev/hello_device c %d 0'.\n", Major );

	return 0;
}

/* This function is called when the module is unloaded */
static void __exit mod_exit(void) {
    unregister_chrdev(Major, DEVICE_NAME);
    printk( KERN_ALERT "Test module is unloaded!\n" );
}

/* Called when a process tries to open the device file. */
static int device_open(struct inode *inode, struct file *file) {
	if (Device_Open)
        return -EBUSY;
	Device_Open++;

	return 0;
}

/* Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file) {
	Device_Open--;

	return 0;
}

/* Called when a process, which already opened the dev file, attempts to read from it. */
static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t * offset) {
    int len = strlen(buf_msg);
    printk(KERN_INFO "=== read : %d\n", length);

    if(length < len)
        return -EINVAL;

    if(*offset != 0) {
        printk( KERN_INFO "=== read return : 0\n" );  // EOF
        return 0;
    }

    if(copy_to_user(buffer, buf_msg, len))
        return -EINVAL;

    *offset = len;
    printk(KERN_INFO "=== read return : %d\n", len);

    return len;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t * offset)
{
	char *msg_from_user;

    msg_from_user = kmalloc(length, GFP_KERNEL);

    if (!msg_from_user){
        printk(KERN_ERR "FAILED kmalloc\n");
        return -1;
    }
    if (copy_from_user(msg_from_user, buffer, length)){
        printk(KERN_ERR "FAILED strncpy_from_user\n");
        return -1;
    }
    printk(KERN_INFO "User write to file");
    kfree(msg_from_user);

    return 0;
}
