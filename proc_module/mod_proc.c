#include "../include/common.h"

static int proc_open(struct inode *inode, struct  file *file);
static ssize_t proc_read(struct file *file, char __user *buffer, size_t size, loff_t *data);
static ssize_t proc_write(struct file *file, const char __user *buffer, size_t size, loff_t *data);


/* callback function's */
static const struct file_operations hello_proc_fops = {
    .owner = THIS_MODULE,
    .open = proc_open,
    .read = proc_read,
    .write = proc_write,
    .release = single_release,
};

static int __init mod_init(void) {
    if(proc_create(NAME_NODE, 0644, NULL, &hello_proc_fops) == 0) {
        printk(KERN_ERR "can't create /proc/%s\n", NAME_NODE);
        return -ENOMEM;
    }
    printk( KERN_INFO "/proc module 'hello' : success!\n");

    return 0;
}

static void __exit mod_exit(void) {
    remove_proc_entry(NAME_NODE, NULL);
    printk(KERN_INFO "/proc/%s removed\n", NAME_NODE);
}

static int proc_open(struct inode *inode, struct  file *file) {
    printk(KERN_ALERT "open_proc: open file\n");
    
	return 0;
}

/* This function is called then the /proc file is read */
static ssize_t proc_read(struct file *file, char __user *buffer, size_t size, loff_t *data) {
    int len = strlen(buf_msg);

    printk(KERN_INFO "procfile_read (/proc/%s) called\n", NAME_NODE);
    if(copy_to_user(buffer, buf_msg, len))
        return -EINVAL;

    return strlen(buf_msg);
}

/* This function is called with the /proc file is written */
static ssize_t proc_write(struct file *file, const char __user *buffer, size_t size, loff_t *data) {
    /* The buffer used to store character */
    static char procfs_buffer[LEN_MSG];
    /* write data to the buffer */
    if (copy_from_user(procfs_buffer, buffer, LEN_MSG)) {
        return -EFAULT;
    }
    printk(KERN_ALERT "write message: %s\n", procfs_buffer);

    return 0;
}
