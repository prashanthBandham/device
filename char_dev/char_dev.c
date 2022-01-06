#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>


#define mem_size 1024

dev_t dev =0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer;

static int __init chr_driver_init(void);
static void __exit chr_driver_exit(void);
static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file,char __user *buf,size_t len,loff_t *off);
static ssize_t my_write(struct file *filp,const char *buf,size_t len,loff_t *off);




static struct file_operation  fops =
{
	.owner          = THIS_MODULE,
	.read           = char_read,
	.Write          = char_write,
	.open           = char_open,
	.release        = char_release,

};

static int my_open(struct inode *inode , struct file * file)
{
	/* create physical memory */
	if((kernel_buffer = kmalloc(mem_size,GFP_KERNEL)) == 0) {
		printk(KERN_INFO "cannot allocated the memory to the kernel..\n");
		return -1;
	}
	printk(KERN_INFO "Device file opened..\n");
	return 0;

}

static my_release(struct inode *inode, stuct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_INFO "Device file closed..\n");
	return 0;
}

static ssize_t my_read(struct file *file,char __user *buf,size_t len,loff_t *off)
{
	copy_to_user(buf,kernel_buffer,mem_size);
	printk(KERN_INFO "Data read done..\n");
	return mem_size;
}
static ssize_t my_write(struct file *filp,const char __user *buf,size_t len, * off)
{
	copy_from_user(kernel_buffer,buf,len);
	printk(KERN_INFO"Data written successfully..\n");
	return len;
}




static int __init char_driver_init(void)
	/*allocation major number*/
	if((alloc_chardev_region(&dev,0,1,"my_Dev")) < 0) {
		printk(KERN_INFO"cannot allocate the major number .\n");
		return -1;
	}
       
        printk(KERN_INFO"Major = %d Minor =%d..\n",MAJOR(dev),MINOR(dev));

	/* creating cdev structer */
	 

	      cdev_init(&my_cdev,&fops);

        /* adding character device to the system */
	      if((cdev_add(&my_cdev,dev,1)) < 0) {
		      printk(KERN_INFO"cannot add the device to the system...\n");
		      goto r_class;
	      }

            /* create struct class */
            if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL) {
		    printk(KERN_INFO "cannot create struct class ...\n");
		    goto r_class;

		}
         
     /* creating device    */
      if((device_create(dev_class,NULL,"my_device")) == NULL) {
	      printk(KERN_INFO "cannot creat the device..\n");
	      goto r_device;
      }
      printk(KERN_INFO"Device driver insert... done properly....\n");
      return 0;

r_device:
              class_destroy(dev_class);







r_class:
	   unregister_chardev_region(dev,1);
	   return -1;



void __exit char_driver_exit(void) {
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chardev_region(dev,1);
	printk(KERN_INFO "Device driver is removed successfully..\n");
}

}
module_init(char_driver_init);
module_exit(char_driver_exit);


MODULE_LICENSE("GPL");




          










