#include "chardev.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */

int ioctl_set_num1(int file_desc, int message)
{
    int ret_val;

    ret_val = ioctl(file_desc, IOCTL_SET_NUM1, message);

    if (ret_val < 0) {
        printf("ioctl_set_msg_num1 failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}



int ioctl_set_num2(int file_desc, int message)
{
    int ret_val;

    ret_val = ioctl(file_desc, IOCTL_SET_NUM2, message);

    if (ret_val < 0) {
        printf("ioctl_set_msg_num2 failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}



int ioctl_get_out(int file_desc)
{
    int ret_val;
  //  int message[100];

    
    ret_val = ioctl(file_desc, IOCTL_GET_OUT, 0);

    if (ret_val < 0) {
        printf("ioctl_get_out failed:%d\n", ret_val);
        exit(-1);
    }

    printf("your random no generated is :%d\n", ret_val);
    return 0;
}




int main()
{
    int file_desc;
	int num1, num2;
	
   char *msg = "Message passed by ioctl\n";

	printf("enter ur no");
	scanf("%d%d",&num1, &num2);

    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    
    
    ioctl_set_num1(file_desc, num1);
    ioctl_set_num2(file_desc, num2);

	ioctl_get_out(file_desc);

    close(file_desc);
    return 0;
}

