#ifndef COMMON_H
#define COMMON_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>
#include <linux/cdev.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Bobrovsky <ileon009@gmail.com>");
MODULE_DESCRIPTION("Test module for linux kernel");

static int  __init mod_init(void);
static void __exit mod_exit(void);
module_init(mod_init);
module_exit(mod_exit);

#define NAME_DIR  "mod_dir"
#define NAME_NODE "mod_hello"
#define LEN_MSG 160
static char buf_msg[LEN_MSG] = "Hello from module!\n";

#endif /* COMMON_H */
