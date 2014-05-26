#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

static int word_count_init(void)
{
    printk("word_count_init_success\n");
    return 0;
}

static void word_count_exit(void)
{
    printk("word_count_exit_success\n");
}

module_init(word_count_init);
module_exit(word_count_exit);
