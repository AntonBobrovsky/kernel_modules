#include "mod_process.h"

static int  __init mod_init(void)
{
    /* Выбираем отправную точку */
    struct task_struct *task = &init_task;

    /* Перебираем элементы списка процессов */
    for_each_process(task) {
        pr_info( "[*] %s [pid = %d], parent '%s'\n", task->comm, task->pid, task->parent->comm);
    }

    return 0;

}

static void __exit mod_exit(void) {
    pr_info( " 'show_process' module is unloaded!\n");
}
