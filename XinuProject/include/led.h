/* led.h - LED Sensor */

#ifndef LED_H
#define LED_H

/* Various Register Addresses to access GPIO */
#define GPIO_0		(0x44E07000)
#define GPIO_1		(0x4804C000)
#define GPIO_2		(0x481AC000)
#define GPIO_3		(0x481AF000)
#define GPIO_OE		(0x134)
#define GPIO_DATAIN	(0x138)
#define GPIO_DATAOUT	(0x13C)

/* Various Function Definitions for LED Sensor */
devcall	ledinit(struct dentry *devptr);
devcall	ledread(struct dentry* devptr, char* buff, int32 count);
devcall	ledwrite(struct dentry* devptr, char* buff, int32 count);

#endif
