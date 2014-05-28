#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "wordcount"
#define TRUE  1
#define FALSE 0
static unsigned char mem[10000];
static char read_flag = 'y';
static int word_count = 0;
static int ret;

static char is_spacewhite(char c)
{
    if(c == ' ' || c == 9 || c == 13 || c == 10)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static int get_count(char *buf)
{
    char flag = FALSE,headFlag = TRUE;
    int n = 0, i = 0;


    while(buf[i] != '\0')
    {

        if(is_spacewhite(buf[i]))
        {
            if(headFlag)
            {
                i++;
                continue;
            }
            if(flag)
            {
                n++;
                flag = FALSE;
            }
        }
        else
        {
            flag = TRUE;
            headFlag = FALSE;
        }
        i++;
    }

    return n;
}

static ssize_t word_count_read(struct file *file, char __user *buf, size_t count , loff_t *ppos)
{
    unsigned char temp[4];
    if(read_flag == 'n')
    {
        temp[0] = word_count >> 24;
        temp[1] = word_count >> 16;
        temp[2] = word_count >> 8;
        temp[3] = word_count;

        copy_to_user(buf, (void*) temp, 4);

        printk("read count:%d\n", (int) word_count);

        read_flag = 'y';
        return word_count;
    }
    else
    {
        return 0;
    }
}

static ssize_t word_count_write(struct file *file, const char __user *buf, size_t count , loff_t *ppos)
{
    copy_from_user(mem, buf, count);
    read_flag = 'n';
    mem[count] = '\0';
    word_count = get_count(mem);
    printk("write count:%d\n",(int) word_count);
    return count;
}

//owner表示设备事件回调函数应用于拿些驱动模块; THIS_MODULE表示应用于当前驱动模块
static struct file_operations dev_fops =
{
    .owner = THIS_MODULE, .read = word_count_read, .write = word_count_write
};

static struct miscdevice misc =
{
    .minor = MISC_DYNAMIC_MINOR, .name = DEVICE_NAME, .fops = &dev_fops
};

static int word_count_init(void)
{
    ret = misc_register(&misc);              //成功注册，返回非0整数，失败返回0
    printk("word_count_init_success:%d\n",ret);
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


