
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>      // Needed by all modules
#include <linux/kernel.h>      // Needed for KERN_INFO
#include <linux/moduleparam.h> // Needed for module_param

/* Necessary because we use the proc fs */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("yinqingwang@gmail.com");
MODULE_DESCRIPTION("This is a hello module!");


static int hello_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m,"Hello module!\nHZ = %d \n", HZ);
    return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
    .owner      = THIS_MODULE,
    .open       = hello_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};


static struct proc_dir_entry *hello_proc_dir = NULL;
static struct proc_dir_entry *hello_proc_file = NULL;

/* Initialize the module - register the proc file */
static int init_hello_module(void)
{
    printk(KERN_ALERT "Hello Proc module: Hello, module is init! \n");
    
    hello_proc_dir = proc_mkdir("hello",NULL);
    if( hello_proc_dir ){
        //0 (zero) means default value of file permissions of 0444
        //hello_proc_file = proc_create("hello", 0, NULL, &hello_proc_fops);
        hello_proc_file = proc_create("hello", 0, hello_proc_dir, &hello_proc_fops);

        if( ! hello_proc_file ){
            proc_remove( hello_proc_dir );  // remove the parent of "/hello/"
            printk("Cann't creat 'hello' in /proc. \n");
            return -1; 
        }
    }

    //A non 0 return means init_module failed; module can't be loaded.
    return 0;
}

/* Remove the module */
static void exit_hello_module(void)
{
    //remove_proc_entry("hello", NULL); this call is ok!
    //proc_remove( hello_proc_file);
    proc_remove( hello_proc_dir );
    printk(KERN_ALERT "Hello Proc module: Goodbye! module exit.\n");
}


//here is the module init/exit
module_init(init_hello_module);
module_exit(exit_hello_module);

