
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>      // Needed by all modules
#include <linux/kernel.h>      // Needed for KERN_INFO
#include <linux/moduleparam.h> // Needed for module_param

/* Necessary because we use the proc fs */
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yinqingwang@gmail.com");
MODULE_DESCRIPTION("This is a hello module!");

/**
 * This structure hold information about the /proc file
 *
 */


/* Put data into the proc fs file.

   Arguments
   =========
   1. The buffer where the data is to be inserted, if 
      you decide to use it.
   2. A pointer to a pointer to characters. This is 
      useful if you don't want to use the buffer 
      allocated by the kernel.
   3. The current position in the file. 
   4. The size of the buffer in the first argument.  
   5. Zero (for future use?).


   Usage and Return Value
   ======================
   If you use your own buffer, like I do, put its 
   location in the second argument and return the 
   number of bytes used in the buffer.

   A return value of zero means you have no further 
   information at this time (end of file). A negative 
   return value is an error condition.
   

   For More Information
   ==================== 
   The way I discovered what to do with this function 
   wasn't by reading documentation, but by reading the 
   code which used it. I just looked to see what uses 
   the get_info field of proc_dir_entry struct (I used a 
   combination of find and grep, if you're interested), 
   and I saw that  it is used in <kernel source 
   directory>/fs/proc/array.c.

   If something is unknown about the kernel, this is 
   usually the way to go. In Linux we have the great 
   advantage of having the kernel source code for 
   free - use it.
 */
static int procfile_read(char *buffer, 
		  char **buffer_location, 
		  off_t offset, 
		  int buffer_length,
		  int* eof,
		  void* data)
		  //int zero)
{
  int len;  /* The number of bytes actually used */

  /* This is static so it will still be in memory 
   * when we leave this function */
  static char my_buffer[80];  

  static int count = 1;

  /* We give all of our information in one go, so if the 
   * user asks us if we have more information the 
   * answer should always be no. 
   *
   * This is important because the standard read 
   * function from the library would continue to issue 
   * the read system call until the kernel replies
   * that it has no more information, or until its 
   * buffer is filled.
   */
  if (offset > 0)
    return 0;

  /* Fill the buffer and get its length */
  len = sprintf(my_buffer, 
    "For the %d%s time, go away!\n", count,
    (count % 100 > 10 && count % 100 < 14) ? "th" : 
      (count % 10 == 1) ? "st" :
        (count % 10 == 2) ? "nd" :
          (count % 10 == 3) ? "rd" : "th" );
  count++;

  /* Tell the function which called us where the 
   * buffer is */
  *buffer_location = my_buffer;

  /* Return the length */
  return len;
}

struct proc_dir_entry *hello_proc_dir;
struct proc_dir_entry *hello_proc_file;

/* Initialize the module - register the proc file */
static int init_hello_module(void)
{
	printk(KERN_ALERT "Hello Proc module: Hello, module is init! \n");
	hello_proc_dir = proc_mkdir("hello",NULL);
	if( hello_proc_dir!=NULL)
	{
		//hello_proc_file = create_proc_entry("hello",0666,hello_proc_dir);
		//hello_proc_file = proc_mkdir_data("hellofile",0655,hello_proc_dir,NULL);
		//hello_proc_file = proc_create_data("hello",0655,hello_proc_dir,NULL,NULL);
		if( hello_proc_file)
		{//not do anything here now!
			//hello_proc_file->data = NULL;
			//hello_proc_file->proc_fops = NULL;//procfile_read;
		}
	}
	else{
		printk("Cann't creat 'hello' dir in /proc. \n");
		return -1;
	} 

	//A non 0 return means init_module failed; module can't be loaded.
	return 0;
}

static void exit_hello_module(void)
{
	proc_remove(hello_proc_dir);

	printk(KERN_ALERT "Hello Proc module: Goodbye! module exit.\n");
}


//here is the module init/exit
module_init(init_hello_module);
module_exit(exit_hello_module);

