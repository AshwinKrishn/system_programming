#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/delay.h> //included later after kthread_run use to cause kernel freeze
#include <linux/semaphore.h>

#define NUM_OF_THREAD 5

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sanfoundry-Manish");
MODULE_DESCRIPTION("Kernel Producer-Consumer Thread assignment");

static struct task_struct *prod[NUM_OF_THREAD], *read[NUM_OF_THREAD];

int buff[64], i=0, thread_num = 0, lock_val=1;

struct semaphore sem_write, sem_read;

int sanfd_producer(void * data)
{
    printk(KERN_INFO "sanfd_producer started\n");
    while (1) 
   {
        if (kthread_should_stop())
            break;
	 /* do_work */
	msleep(1000); //to prevent the kernel freeze
	if(i<64)
	{
		down(&sem_read);
		down(&sem_write); //write lock: critical section
		i++;
		*(((int *)data) +(i-1))=i;
		printk("Worker: Work Sequence %d\n", *(((int *)data) +(i-1)));
		up(&sem_read);
		up(&sem_write);	//critical section over: unlocked

    	}//if end
    } //while end
    return 0;
} //Producer

int sanfd_consumer(void * data)
{
    printk(KERN_INFO "sanfd_consumer started\n");
    while (1) {
        if (kthread_should_stop())
            break;
        /* do_work */
	msleep(1000);
	if(i<64)
	{
		down(&sem_write);
		down(&sem_read); //lock: critical section
		printk("Reader: Reading %d\n", *(((int *)data)+(i-1)));
		up(&sem_write);	//critical section over: unlocked
		up(&sem_read);
		
	}
	
    }//while
    return 0;
}

void cleanup_worker_threads(void)
{
    /*
     * Create Producer and Consumer Threads
     * kthread_stop(task struct *)
     */
	//Stop writers
	kthread_stop(prod[0]);
	kthread_stop(prod[1]);
	kthread_stop(prod[2]);
	kthread_stop(prod[3]);
	kthread_stop(prod[4]);

	//Stop readers
	kthread_stop(read[0]);
	kthread_stop(read[1]);
	kthread_stop(read[2]);
	kthread_stop(read[3]);
	kthread_stop(read[4]);
}

void init_worker_threads(void)
{

    /*
     * Create Producer and Consumer Threads
     * kthread_run(sanfd_producer,arg,"sanfd_prod/%d",i);
     * kthread_run(sanfd_consumer,arg,"sanfd_cons/%d",i);
     */	

	//writer1
	thread_num++;
	/*while(thread_num < 5)
	{
		if((thread_num % 2) != 0)
		{
			
		}
			
	}*/
	prod[0] = kthread_run(sanfd_producer, buff, "sanfd_prod/%d",thread_num);

	//reader1
	read[0] = kthread_run(sanfd_consumer, buff, "sanfd_cons/%d",thread_num);

	thread_num++;
	prod[1] = kthread_run(sanfd_producer, buff, "sanfd_prod/%d",thread_num);

	//reader2;
	read[1] = kthread_run(sanfd_consumer, buff, "sanfd_cons/%d",thread_num);
	
thread_num++;
	//writer3
	prod[2] = kthread_run(sanfd_producer, buff, "sanfd_prod/%d",thread_num);

	//reader3;
	read[2] = kthread_run(sanfd_consumer, buff, "sanfd_cons/%d",thread_num);

thread_num++;
	//writer4
	prod[3] = kthread_run(sanfd_producer, buff, "sanfd_prod/%d",thread_num);

	//reader4;
	read[3] = kthread_run(sanfd_consumer, buff, "sanfd_cons/%d",thread_num);


thread_num++;
	//writer5
	prod[4] = kthread_run(sanfd_producer, buff, "sanfd_prod/%d",thread_num);

	//reader5;
	read[4] = kthread_run(sanfd_consumer, buff, "sanfd_cons/%d",thread_num);		
}

static int __init sanfd_kthread_init(void)
{
    printk(KERN_INFO "Loaded kthreadwork module\n");

    sema_init(&sem_write,lock_val);
    sema_init(&sem_read,lock_val);
    init_worker_threads();

    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit sanfd_kthread_cleanup(void)
{
    printk(KERN_INFO "Cleaning up kthreadwork module.\n");
    cleanup_worker_threads();
}

module_init(sanfd_kthread_init);
module_exit(sanfd_kthread_cleanup);

