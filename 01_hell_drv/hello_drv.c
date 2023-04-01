#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>

// 确定主设备号
static int major = 0;
static char kernel_buf[1024];
static struct class *hello_class;

#define MIN(a, b) (a < b ? a : b)

static ssize_t hello_drv_read(struct file *file, char __user *buf, size_t size, loff_t *offset)
{
    int err;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    err = copy_to_user(buf, kernel_buf, MIN(1024, size));
    return MIN(1024, size);
}

static ssize_t hello_drv_write(sturct file *file, const char __user *buf, size_t size, loff_t *offset)
{
    int err;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    err = copy_from_user(kernel_buf, buf, MIN(1024, size));
    return MIN(1024, SIZE);
}

static int hello_drv_open(struct inode* node, struct file *file)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static int hello_drv_close(struct inode* node, struct file *file)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

// 自定义 file_operations
static struct file_operations hello_drv = {
    .owner      = THIS_MODULE,
    .open       = hello_drv_open;
    .read       = hello_drv_read;
    .write      = hello_drv_write;
    .release    = hello_drv_close;
};

// 注册
static int __int hello_init(void)
{
    int err;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    major = register_chrdev(0, "hello", &hello_drv);

    // class_create 用于创建一个设备类的函数，设备类是一组相关的设备的集合，通常用于管理设备节点的创建和销毁
    // class_create 函数原型 truct class *class_create(struct module *owner, const char *name);
    // onwen 参数是指定该设备类的所有者模块, name 参数是指定该设备类的名称，可以在 sysfs 中看到
    hello_class = class_create(THIS_MODULE, "hello_class");
    
    //　用于读取　helloc_class 指针中的错误代码
    err = PTR_ERR(hello_class);
    if (IS_ERR(hello_class)) {
        printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
        unregister_chrdev(major, "hello");
        return -1;
    }

    // 在 /dev 下创建 hello 设备节点 
    device_create(hello_class, NULL, MKDEV(major, 0), NULL, "hello");

    return 0;
}

static void __exit hello_exit(void)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    device_destroy(hello_class, MKDEV(major, 0));
    class_destroy(hello_class);
    unregister_chrdev(major, "hello");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
