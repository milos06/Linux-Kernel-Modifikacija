#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched/signal.h>
#include <linux/fdtable.h>
#include <linux/mm.h>
#include <linux/cred.h>
#include <linux/timekeeping.h>
#include <linux/slab.h>

static char *filepath = "/tmp/testfile.txt";
module_param(filepath, charp, 0000);

static int __init hello_init(void)
{
    struct file *target_file;
    struct inode *target_inode;
    struct task_struct *task;

    printk(KERN_INFO "===== MODULE LOADED =====\n");
    printk(KERN_INFO "Target file: %s\n", filepath);

    target_file = filp_open(filepath, O_RDONLY, 0);
    if (IS_ERR(target_file)) {
        printk(KERN_INFO "Cannot open file\n");
        return PTR_ERR(target_file);
    }

    target_inode = file_inode(target_file);

    printk(KERN_INFO "Searching processes using inode: %lu\n",
           target_inode->i_ino);

    for_each_process(task) {

        struct files_struct *files;
        struct fdtable *fdt;
        unsigned int i;

        files = task->files;
        if (!files)
            continue;

        spin_lock(&files->file_lock);
        fdt = files_fdtable(files);

        for (i = 0; i < fdt->max_fds; i++) {

            struct file *file = fdt->fd[i];

            if (file &&
                file_inode(file)->i_ino == target_inode->i_ino &&
                file_inode(file)->i_sb == target_inode->i_sb) {

                kuid_t uid = task_uid(task);
                unsigned long mem = 0;
                unsigned long utime, stime;

                if (task->mm)
                    mem = (task->mm->total_vm << (PAGE_SHIFT - 10));

                utime = task->utime;
                stime = task->stime;

                printk(KERN_INFO
                       "PID: %d | Name: %s | UID: %d | Prio: %d | Nice: %d | Mem: %lu KB | CPU time: %lu\n",
                       task->pid,
                       task->comm,
                       __kuid_val(uid),
                       task->prio,
                       task_nice(task),
                       mem,
                       utime + stime);
            }
        }

        spin_unlock(&files->file_lock);
    }

    filp_close(target_file, NULL);

    printk(KERN_INFO "===== END OF SEARCH =====\n");

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "===== MODULE UNLOADED =====\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
