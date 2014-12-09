
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>      // Needed by all modules
#include <linux/kernel.h>      // Needed for KERN_INFO
#include <linux/moduleparam.h> // Needed for module_param

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yinqingwang@gmail.com");
MODULE_DESCRIPTION("This is a hello module!");

static int N=3;

module_param(N,int, 0644);

int say_hello(int n)
{
	printk(KERN_ALERT " Hello world! param N is : %d \n", n);
	N = n;
	return 0;
}

static int init_hello(void)
{
	printk(KERN_ALERT "Hello module: Hello, module is init! param N is :%d \n", N);

	//A non 0 return means init_module failed; module can't be loaded.
	return 0;
}

static void exit_hello(void)
{
	printk(KERN_ALERT "Hello module: Goodbye! module exit.\n");
}

//here is the export symbol 
EXPORT_SYMBOL(say_hello);

//here is the module init/exit
module_init(init_hello);
module_exit(exit_hello);


