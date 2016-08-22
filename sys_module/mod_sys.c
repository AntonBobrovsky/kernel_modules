#include "../include/common.h"

static struct kobject *example_kobject;
static int foo;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
	int ret;

	ret = kstrtoint(buf, 10, &foo);
	if (ret < 0)
		return ret;

	return count;
}

static struct kobj_attribute foo_attribute =
    __ATTR(foo, 0664, foo_show, foo_store);

static int __init mod_init (void) {
    int error = 0;

    printk(KERN_INFO "Module initialized successfully \n");

    example_kobject = kobject_create_and_add("kobject_example", kernel_kobj);
    if(!example_kobject)
        return -ENOMEM;

    error = sysfs_create_file(example_kobject, &foo_attribute.attr);
    if (error) {
        pr_debug("failed to create the foo file in /sys/kernel/kobject_example \n");
    }

    return error;
}

static void __exit mod_exit (void) {
        printk(KERN_INFO "Module un initialized successfully \n");
        kobject_put(example_kobject);
}
