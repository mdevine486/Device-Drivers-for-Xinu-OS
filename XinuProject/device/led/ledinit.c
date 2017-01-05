/* ledinit.c - LED Initialization */

#include <xinu.h>

devcall	ledinit(struct dentry *devptr){
	char buff[1];
	buff[0]='0';
	write(LED,(char*)buff,1);
	return 1;
}
