/* ledread.c - LED Reading Values */

#include <xinu.h>

devcall	ledread(struct dentry* devptr, char* buff, int32 count){
	// Set Direction as IN
	#include <ddl_led_dir_in.inc>
	// Read the Value
	int32 val = 
	#include <ddl_led_read.inc>
	buff[0] = val + 48;
	write(LED,(char*)buff,1);
	return 1;
}
