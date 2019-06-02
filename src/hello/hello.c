
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>      // Needed by all modules
#include <linux/kernel.h>      // Needed for KERN_INFO
#include <linux/moduleparam.h> // Needed for module_param

#include <linux/sched.h>       // pointer of Process, current


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
	printk(KERN_ALERT "Inside the %s function.\n", __FUNCTION__);
	
    printk(KERN_ALERT "Hello module: Hello, module is init! param N is :%d \n", N);

    /** 测试通过current（struct task_struct）获取当前进程名字和进程号，需要头文件linux/sched.h  * 
     *  KERN_INFO相当于字符串""，即不显示任何内容，然而我们建议在程序中注明，以表示信息的   * 
     *  级别，使程序更为规范和可读 
     */ 
    printk(KERN_INFO "The Process is [%s], PID [%i]/n", current->comm,current->pid); 
	
    //A non 0 return means init_module failed; module can't be loaded.
	return 0;
}

static void exit_hello(void)
{
	printk(KERN_ALERT "Inside the %s function.\n", __FUNCTION__);

	printk(KERN_ALERT "Hello module: Goodbye! module exit.\n");
}

//here is the export symbol 
EXPORT_SYMBOL(say_hello);

//here is the module init/exit
module_init(init_hello);
module_exit(exit_hello);


