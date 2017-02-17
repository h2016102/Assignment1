Following program takes two inputs from user(a range by min and max no) and then generates a random no.

For this two programs have written , one for kernel space and other for user space.

user space prog takes two inputs from user and using IOCTL calls it send to kernel and kernel after manipulation generates a random no that is sent to user space by IOCTL calls.





commands followed step by step :

1. make                            // for compilation
2. sudo insmod ./trng.ko          //to build kernel module
3. mknod sudo mknod /dev/char_dev c 100 0        // to create device file
4. gcc -o -g user_prog user_prog.c               // for user program compilation
5. ./user_prog                                   //to run user program

# Assignment1
