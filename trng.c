#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>        /* for get_user and put_user */
#include <linux/time.h>
#include <linux/init.h>
//#include <linux/sys/io.h>

#include "chardev.h"
#define SUCCESS 0
#define DEVICE_NAME "char_dev"
#define BUF_LEN 80

static int Device_Open = 0;
char Message[BUF_LEN];
static char *Message_Ptr;

static int  num1, num2, out;
  //int sec;

struct timespec ts;

static long int sec;


static int device_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
        printk(KERN_INFO "device_open(%p)\n", file);
#endif

    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    
    Message_Ptr = Message;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
    printk(KERN_INFO "device_release(%p,%p)\n", inode, file);
#endif

    Device_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}

static long device_ioctl(struct file *file,             /* ditto */
                  unsigned int ioctl_num,        /* number and param for ioctl */
                  unsigned int ioctl_param)
{
    
   
   	 switch (ioctl_num)


 {
case IOCTL_SET_NUM1:
        
        	num1 = ioctl_param;

  		printk(KERN_INFO "print:%d \n", num1);
		break;

case IOCTL_SET_NUM2:
       
         num2 = ioctl_param;
	printk(KERN_INFO "number 2 is :%d \n",num2);
         break;



    case IOCTL_GET_OUT:

ts = current_kernel_time();

sec = ts.tv_sec;
//int i = 0;
        

 //sec = 40;
if(num2>0&&num1>0&&(num2-num1)>=2)

	{
		//while(1)
		//{
		out =sec%3600;
		}
	

	                  /*if(num2>=sec && num1<=sec)
		{
		printf("%d\n",sec);
		break;
		}
	if(num2>num1)
	{
	no =(sec-num1)%(num2-num1) + num1;
	}*/
	
	
	else
	{
		out =0;	
	}
	
	//out = sec; 
        
	printk(KERN_INFO "your random number is.. %d\n",out);
	return (out);
	break;


}
    return SUCCESS;
}

struct file_operations Fops = {
  
        .unlocked_ioctl = device_ioctl,
        .open = device_open,
        .release = device_release,      
};


int init_module(void)
{
    int ret_val;
    
    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

    
    if (ret_val < 0) {
        printk(KERN_ALERT "%s failed with %d\n",
               "Sorry, registering the character device ", ret_val);
        return ret_val;
    }

    printk(KERN_INFO "%s The major device number is %d.\n",
           "Registeration is a success", MAJOR_NUM);
    printk(KERN_INFO "If you want to talk to the device driver,\n");
    printk(KERN_INFO "you'll have to create a device file. \n");
    printk(KERN_INFO "We suggest you use:\n");
    printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
    printk(KERN_INFO "The device file name is important, because\n");
    printk(KERN_INFO "the ioctl program assumes that's the\n");
    printk(KERN_INFO "file you'll use.\n");

    return 0;
}


 void cleanup_module(void)
{
    
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	
}



