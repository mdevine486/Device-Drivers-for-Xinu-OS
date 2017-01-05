/* tmpread.c - Temperature Sensor Reading Values */

#include <xinu.h>

devcall	tmpread(struct dentry* devptr, char* buff, int32 count){
	AT_ADDRESS(ADC_BASE + STEPENABLE) |= (0x01<<1);
	unsigned int data = 0;
	int sampleNum = AT_ADDRESS(ADC_BASE + FIFO0COUNT);
	int i;
	for(i = 0; i < sampleNum; i++)
	{
		data = 
		#include<ddl_tmp_read.inc>
	}
	buff[3] = (data&(0xff000000))>>24;
	buff[2] = (data&(0x00ff0000))>>16;	
	buff[1] = (data&(0x0000ff00))>>8;
	buff[0] = (data&(0x000000ff));

	return 1;
}
