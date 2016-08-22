#ifndef MOD_PROCESS_H
#define MOD_PROCESS_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Bobrovsky <ileon009@gmail.com>");
MODULE_DESCRIPTION("Test module for linux kernel");

static int  __init mod_init(void);
static void __exit mod_exit(void);
module_init(mod_init);
module_exit(mod_exit);

#endif /* MOD_PROCESS_H */
