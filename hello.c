#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched/signal.h>
#include <linux/fdtable.h>
#include <linux/mm.h>

static char *filepath = "/tmp/testfile.txt";
module_param(filepath, charp, 0000);

static int __init hello_init(void)
{
    struct file *target_file;
    struct inode *target_inode;
    struct task_struct *task;

    printk(KERN_INFO "Module loaded\n");

    /* Otvori fajl u kernelu */
    target_file = filp_open(filepath, O_RDONLY, 0);
    if (IS_ERR(target_file)) {
        printk(KERN_INFO "Ne mogu da otvorim fajl\n");
        return PTR_ERR(target_file);
    }

    target_inode = file_inode(target_file);

    printk(KERN_INFO "Trazim procese koji koriste inode: %lu\n",
           target_inode->i_ino);

    /* Prolaz kroz sve procese */
    for_each_process(task) {

        struct files_struct *files = task->files;
        struct fdtable *fdt;
        unsigned int i;

        if (!files)
            continue;

        spin_lock(&files->file_lock);
        fdt = files_fdtable(files);

        for (i = 0; i < fdt->max_fds; i++) {

            struct file *file = fdt->fd[i];

            if (file && file_inode(file) == target_inode) {

                printk(KERN_INFO
                       "PID: %d | Name: %s | Prio: %d | Nice: %d | Mem: %lu KB\n",
                       task->pid,
                       task->comm,
                       task->prio,
                       task_nice(task),
                       task->mm ? (task->mm->total_vm << (PAGE_SHIFT - 10)) : 0);
            }
        }

        spin_unlock(&files->file_lock);
    }

    filp_close(target_file, NULL);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
