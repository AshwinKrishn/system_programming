#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");

extern struct task_struct init_task;

static int pscode_init(void)
{
    	static struct task_struct * next  ;
	next =  list_entry((init_task.tasks.next),struct task_struct,tasks); 
  	printk(KERN_INFO "Initializing Pscode Module\n");
    	printk(KERN_INFO"pid=%d name = %s\n",init_task.pid,init_task.comm);    

	do{
		printk(KERN_INFO"pid=%d name = %s\n",next->pid,next->comm);


		next =  list_entry((next->tasks.next),struct task_struct,tasks);

	}while(next != &init_task); 

	return 0;
}

static void pscode_exit(void)
{
    printk(KERN_INFO "Exiting Pscode Module\n");
}

module_init(pscode_init);
module_exit(pscode_exit);

