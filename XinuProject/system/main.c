/*  main.c  - main */

#include <xinu.h>

void sendData(uint32 data){
	uint32 remip	= 0xC0A80066; 		/* Remote IP address or zero */
	uint16 remport	= 5555;			/* Remote UDP protocol port */
	uint16 locport	= 5555;			/* Local UDP protocol port */
	
	int slot = 0;
	slot = udp_register(0xC0A80067, 8080, 8080);
	if (slot == SYSERR) {
		fprintf(stderr,"\nCould not reserve UDP port %d.",locport);
	}

	char msg[1];
	msg[0]=data+48;
	int32 msglen = 1;
	int retval=0;
	
	retval = udp_send(slot, msg, msglen);
	if (retval == SYSERR) {
		fprintf(stderr, "\nError Sending UDP Data!");
		return 1;
	}
	udp_release(slot);
	printf("\nSent %u out to Network.",data);
}

uint32 receiveData(){
	/*char ch=getc(0);
	char flush=getc(0);
	uint32 data=ch-48;
	printf("\nReceived %u from Network.",data);
	return data;*/

	uint32 remip	= 0xC0A80067; 		/* Remote IP address or zero */
	uint16 remport	= 8080;			/* Remote UDP protocol port */
	uint16 locport	= 8080;			/* Local UDP protocol port */
	
	int slot = 0;
	slot = udp_register(remip, remport, locport);
	if (slot == SYSERR) {
		fprintf(stderr,"\nCould not reserve UDP port %d.",locport);
	}

	char msg[2];
	int32 	msglen	=	1;
	int32 	retval	=	0;
	int32	delay	= 	40000;
	
	retval = udp_recv(slot, msg, sizeof(msg), delay);
	if (retval == TIMEOUT){
		fprintf(stderr, "\nTIMEOUT...!");
	}
	else if (retval == SYSERR){
		fprintf(stderr, "\nError Receiving UDP Data!");
	}
	udp_release(slot);
	uint32 data=msg[0]-48;
	//printf("\nReceived %s out to Network.",msg);
	printf("\nReceived %u from Network.",data);
	return data;
}

uint32 readLED(){
	char buff[1];
	read(LED,(char*)buff,1);
	uint32 res = buff[0]-48;
	return res;
}

void writeLED(uint32 data){
	char buff[1];
	buff[0]=data+48;
	write(LED,(char*)buff,1);
}

void writeSSD(uint32 data){
	char *buff;
	switch(data){
		case 0:	buff="11111100";
			write(SSD,(char*)buff,8);
			break;
		case 1:	buff="01100000";
			write(SSD,(char*)buff,8);
			break;
		case 2:	buff="11011010";
			write(SSD,(char*)buff,8);
			break;
		case 3:	buff="11110010";
			write(SSD,(char*)buff,8);
			break;
		case 4:	buff="01100110";
			write(SSD,(char*)buff,8);
			break;
		case 5:	buff="10110110";
			write(SSD,(char*)buff,8);
			break;
		case 6:	buff="10111110";
			write(SSD,(char*)buff,8);
			break;
		case 7:	buff="11100000";
			write(SSD,(char*)buff,8);
			break;
		case 8:	buff="11111110";
			write(SSD,(char*)buff,8);
			break;
		case 9:	buff="11100110";
			write(SSD,(char*)buff,8);
			break;
		case 10:buff="00000001";
			write(SSD,(char*)buff,8);
	}
}

char* readTMP(){
	char data[4];
	read(TMP,(char*)data,4);
	read(TMP,(char*)data,4);
	return data;
}

process	main(void)
{
	//sendData(8);
	//receiveData();
	uint32 usr_in;
	char ch,flush;
	uint32 LED_STATUS, SSD_STATUS, TMP_STATUS;
	LED_STATUS = SSD_STATUS = TMP_STATUS = 0;
	printf("\nLED Connected? (y/n) : ");
	ch=getc(0);
	flush=getc(0);
	if(ch=='y' || ch=='Y'){
		LED_STATUS=1;
	}
	printf("\nSSD Connected? (y/n) : ");
	ch=getc(0);
	flush=getc(0);
	if(ch=='y' || ch=='Y'){
		SSD_STATUS=1;
	}
	printf("\nTMP Connected? (y/n) : ");
	ch=getc(0);
	flush=getc(0);
	if(ch=='y' || ch=='Y'){
		TMP_STATUS=1;
	}
	unsigned int vol;
	unsigned int integer = 0;
	unsigned int decimal = 0;
	float voltage;

	char *data;
	while(TRUE){
		uint32 input = receiveData();
		uint32 num;
		switch(input){
			case 0: sendData(LED_STATUS);
				break;
			case 1: sendData(SSD_STATUS);
				break;
			case 2: sendData(TMP_STATUS);
				break;
			case 3: if(LED_STATUS==1){
					sendData(readLED());
				}
				else{
					sendData(-1);
				}
				break;
			case 4: if(LED_STATUS==1){
					writeLED(1);
					sendData(1);
				}
				else{
					sendData(-1);
				}
				break;
			case 5: if(LED_STATUS==1){
					writeLED(0);
					sendData(1);
				}
				else{
					sendData(-1);
				}
				break;
			case 6: if(SSD_STATUS==1){
					sendData(1);
					num=receiveData();
					writeSSD(num);
					sendData(1);
				}
				else{
					sendData(-1);
				}
				break;
			case 7: if(TMP_STATUS==1){
					sendData(1);
					data=readTMP();
					vol = *(unsigned int*)data;
					voltage = (vol*1.8/4095)*1000;
					integer = (unsigned int)voltage;
					decimal = (unsigned int)((voltage - integer)*10);
					sleep(1);
					sendData(integer/100);
					sleep(1);
					sendData((integer/10)%10);
					sleep(1);
					sendData(integer%10);
					//sendData(decimal);
				}
				else{
					sendData(-1);
				}
				break;
		}
	}

	return OK;
}
