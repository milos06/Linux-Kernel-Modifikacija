#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/dcache.h>

static char *filepath = "/tmp/testfile.txt";
module_param(filepath, charp, 0000);
MODULE_PARM_DESC(filepath, "Putanja do fajla");

static int __init hello_init(void)
{
    struct path path;
    struct inode *inode;
    int ret;

    printk(KERN_INFO "Module loaded\n");
    printk(KERN_INFO "Putanja: %s\n", filepath);

    /* Pretvara putanju u kernel path */
    ret = kern_path(filepath, LOOKUP_FOLLOW, &path);
    if (ret) {
        printk(KERN_INFO "Ne mogu da nadjem fajl\n");
        return ret;
    }

    /* Uzmi inode */
    inode = d_inode(path.dentry);

    printk(KERN_INFO "Inode broj je: %lu\n", inode->i_ino);

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
