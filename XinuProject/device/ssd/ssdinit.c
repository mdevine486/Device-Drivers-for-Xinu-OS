/* ssdinit.c - SSD Initialization */

#include <xinu.h>

devcall	ssdinit(struct dentry *devptr){
	char *buff;
	buff="00000000";
	write(SSD,(char*)buff,8);
	return 1;
}
