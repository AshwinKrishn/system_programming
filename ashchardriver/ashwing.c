#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/uaccess.h>  

MODULE_LICENSE("GPL");              /// type -- this affects runtime behavior
MODULE_AUTHOR("Ashwin");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple char driver for the BBB.");  ///<on -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module
 
static char *name = "world";        ///< An example LKM argume is "world"
module_param(name, charp, S_IRUGO); /// ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///cription
static dev_t ashwing_dev;
static struct class * ashwing_class;
static struct cdev	ashwing_cdev;

static char ash[256] = {0};
static int ash_len;

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: read()\n");
    if (*off == 0)
    { 
        if (copy_to_user(buf, ash, ash_len) != 0)
            return -EFAULT;
        else
        {
            (*off)++;
            return ash_len;
        }
    }
    else
        return (ash_len = 0); 		
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: write() witth %zu bytes\n",len);
    if(copy_from_user(ash,buf,len) != 0){
	return -EFAULT;
    }
    else{
	int i = 0,j = (int)len;
	ash_len = len;
	printk(KERN_INFO"the string is :::: ");
	for(i = 0; i < j;i++){
    		printk(KERN_INFO "%c",*(ash+i));
	}
	printk(KERN_INFO"\n string print from write done");
	return len;
    }
}
static struct file_operations ashwing_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init ash_init(void){

	int retval;
	static struct device *  ashwing_device;
	printk(KERN_INFO"Initialization");

	if((retval = alloc_chrdev_region(&ashwing_dev,0,3,"ashwing")) < 0){
		printk(KERN_INFO"major minor alloc  failed");
		return retval;
	}
	if(IS_ERR(ashwing_class =  class_create(THIS_MODULE,"ashwing_class"))){
		printk(KERN_INFO"class create failed");	
		unregister_chrdev_region(ashwing_dev,3);
		return PTR_ERR(ashwing_class);
	}
	if(IS_ERR( ashwing_device = device_create(ashwing_class,NULL,ashwing_dev,NULL,"dev_ashwing") )){
		printk(KERN_INFO"dev create failed");
		class_destroy(ashwing_class);
	        unregister_chrdev_region(ashwing_dev,3);
		return PTR_ERR(ashwing_class);
	}
	
	cdev_init(&ashwing_cdev,&ashwing_fops);
	if((retval = cdev_add(&ashwing_cdev,ashwing_dev,3)) < 0){
		printk(KERN_INFO"cdev add failed");
		device_destroy(ashwing_class,ashwing_dev);
		class_destroy(ashwing_class);
                unregister_chrdev_region(ashwing_dev,3);
		return retval;
	}
	printk(KERN_INFO "successfully created <Major, Minor>: <%d, %d>\n", MAJOR(ashwing_dev), MINOR(ashwing_dev));
	
	return 0;
}


static void __exit ash_exit(void){

	cdev_del(&ashwing_cdev);
	device_destroy(ashwing_class,ashwing_dev);
	class_destroy(ashwing_class);
	unregister_chrdev_region(ashwing_dev,3);
	printk(KERN_INFO"exiting");
}

module_init(ash_init);
module_exit(ash_exit);
