/* ledwrite.c - LED Writing Values */

#include <xinu.h>

devcall	ledwrite(struct dentry* devptr, char* buff, int32 count){
	// Set Direction as OUT
	#include<ddl_led_dir_out.inc>
	// Write the Value
	int32 val = buff[0] - 48;
	switch(val){
		#include <ddl_led_write.inc>
	}
	return 1;
}
