#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "wordcount"

//owner表示设备事件回调函数应用于拿些驱动模块; THIS_MODULE表示应用于当前驱动模块
static struct file_operations dev_fops =
{
    .owner = THIS_MODULE
};

static struct miscdevice misc =
{
    .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops
};

static int word_count_init(void)
{
    int ret;
    ret = misc_register(&misc);              //成功注册，返回非0整数，失败返回0
    printk("word_count_init_success\n");
    return ret;
}

static void word_count_exit(void)
{
    misc_deregister(&misc);
    printk("word_count_exit_success\n");
}

module_init(word_count_init);
module_exit(word_count_exit);

MODULE_AUTHOR("MC");
MODULE_DESCRIPTION("statistics of word count.");
MODULE_ALIAS("word count module.");
MODULE_LICENSE("GPL");
