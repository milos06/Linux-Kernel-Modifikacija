#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/dcache.h>
#include <linux/sched/signal.h>

static char *filepath = "/tmp/testfile.txt";
module_param(filepath, charp, 0000);

static int __init hello_init(void)
{
    struct path path;
    struct inode *inode;
    struct task_struct *task;
    int ret;

    printk(KERN_INFO "Module loaded\n");

    /* Pronadji inode fajla */
    ret = kern_path(filepath, LOOKUP_FOLLOW, &path);
    if (ret) {
        printk(KERN_INFO "Ne mogu da nadjem fajl\n");
        return ret;
    }

    inode = d_inode(path.dentry);

    printk(KERN_INFO "Inode broj: %lu\n", inode->i_ino);

    printk(KERN_INFO "Lista svih procesa:\n");

    /* Prolaz kroz sve procese */
    for_each_process(task) {
        printk(KERN_INFO "PID: %d | Ime: %s\n",
               task->pid,
               task->comm);
    }

    path_put(&path);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
