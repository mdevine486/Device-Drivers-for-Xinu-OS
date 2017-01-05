/* tmp.h - Temperature Sensor */

#ifndef TMP_H
#define TMP_H

/* Various Register Addresses to access AIN0 */
#define	ADC_BASE		(0x44E0D000)
#define CTRL			(0x40)
#define	ADC_CLKDIV		(0x4C)
#define STEPENABLE		(0x54)
#define STEPCONFIG1		(0x64)
#define FIFO0COUNT		(0xE4)
#define FIFO0DATA		(0x100)

#define CM_WKUP			(0x44E00400)
#define CM_WKUP_CLKSTCTRL	(0x00)
#define CM_WKUP_CONTROL_CLKCTRL	(0x04)
#define CM_WKUP_ADC_TSC_CLKCTRL	(0xBC)

/* Various Function Definitions for Temperatue Sensor */
devcall	tmpinit(struct dentry *devptr);
devcall	tmpread(struct dentry* devptr, char* buff, int32 count);

#endif
