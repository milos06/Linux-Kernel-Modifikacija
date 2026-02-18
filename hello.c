#include <linux/module.h>
#include <linux/kernel.h>

static char *filepath = "/tmp/testfile.txt";

module_param(filepath, charp, 0000);
MODULE_PARM_DESC(filepath, "Putanja do fajla");

static int __init hello_init(void)
{
    printk(KERN_INFO "Module loaded\n");
    printk(KERN_INFO "Fajl je: %s\n", filepath);
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
