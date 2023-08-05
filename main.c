#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
// #include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kill_your_soul");
MODULE_DESCRIPTION("A Linux module.");
MODULE_VERSION("0.0.1");


static char *message = "Hello from kernel module\n";
static int timer_clock = 5000;
static struct timer_list my_timer;
static char *path = "/tmp/test.txt";

module_param(path, charp, S_IRWXU);
MODULE_PARM_DESC(path, "Path to the file");
module_param(timer_clock, int, S_IRWXU);
MODULE_PARM_DESC(timer_clock, "An integer of the timer clock");


static void write_to_file(const char *path) {
    struct file *file;
    ssize_t ret;

    // Open the file for writing
    file = filp_open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (IS_ERR(file)) {
        pr_err("Failed to open file %s\n", path);
        pr_err("Error code: %ld\n", PTR_ERR(file));
        return;
    }

    // Write the message to the file
    pr_info("f_pos = %lld\n", file->f_pos);
    ret = kernel_write(file, message, strlen(message), &file->f_pos);
    if (ret < 0) {
        pr_err("Failed to write to file: %s\n", path);
    }

    // Close the file
    filp_close(file, NULL);
}


// static void write_to_file(const char *path) {
//     struct file *file;
//     mm_segment_t fs;
//     ssize_t ret;
//     file = filp_open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
//     if (IS_ERR(file)) {
//         pr_err("Failed to open file %s\n", path);
//         return;
//     }

//     fs = get_fs();
//     set_fs(KERNEL_DS);
//     ret = vfs_write(file, message, strlen(message), &file->f_pos);
//     if (ret < 0) {
//         pr_err("Failed to write to file %s\n", path);
//     }

//     set_fs(fs);
//     filp_close(file, NULL);
// }

static void my_timer_callback(struct timer_list *timer) {
    // pr_info("Hello, World! from the timer callback function timer_clock=%d\n", timer_clock);
    my_timer.expires = jiffies + msecs_to_jiffies(timer_clock);
    write_to_file(path);
    add_timer(&my_timer);
}

static int __init lkm_example_init(void) {
    // pr_info("Hello, World! from pr_info %d\n", hello3_data);
    pr_info("timer_clock = %d\n", timer_clock);
    timer_setup(&my_timer, my_timer_callback, 0);
    my_timer.expires = jiffies + msecs_to_jiffies(timer_clock);
    add_timer(&my_timer);
    return 0;
}
static void __exit lkm_example_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
    del_timer(&my_timer);
}
module_init(lkm_example_init);
module_exit(lkm_example_exit);
