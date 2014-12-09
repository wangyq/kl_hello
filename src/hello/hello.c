
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

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

EXPORT_SYMBOL(say_hello);

static int init_hello(void)
{
	printk(KERN_ALERT "hello module: Hello, module is init! param N is :%d \n", N);
	return 0;
}

static void exit_hello(void)
{
	printk(KERN_ALERT "Hello module: Goodbye! module exit.\n");
}

module_init(init_hello);
module_exit(exit_hello);


