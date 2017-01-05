/* tmpinit.c - Temperature Sensor Initialization */

#include <xinu.h>

devcall	tmpinit(struct dentry *devptr){
	// Initialize Clock
	// Enable Mandatory Clock
	AT_ADDRESS(CM_WKUP + CM_WKUP_CONTROL_CLKCTRL) |= 0x02;
	// Wait to Wake Up
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_CONTROL_CLKCTRL) & 0x03) != 0x02);
	// Forced Wake Up Call For Transition
	AT_ADDRESS(CM_WKUP + CM_WKUP_CLKSTCTRL) |= 0x02;
	// Wait to Wake Up
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_CLKSTCTRL) & 0x03) != 0x02);
	// Enable Mandatory Clock
	AT_ADDRESS(CM_WKUP + CM_WKUP_ADC_TSC_CLKCTRL) |= 0x02;
	// Wait to Wake Up
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_ADC_TSC_CLKCTRL) & 0x03) != 0x02);
	// Wait for Module to be Fully Functional
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_CONTROL_CLKCTRL) & (0x03<<16)) != 0x00);
	// Wait for Clock to be gated
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_CLKSTCTRL) & (0x01<<14)) == 0x00 );
	// Wait for Module to be Fully Functional
	while((AT_ADDRESS(CM_WKUP + CM_WKUP_ADC_TSC_CLKCTRL) & (0x03<<16)) != 0x00);

	// Set Clock Frequency
	unsigned int div=24000000/3000000 - 1;
	// Clearing the Value
	AT_ADDRESS(ADC_BASE + ADC_CLKDIV) &= ~(0xFFFF);
	// Set the Value
	AT_ADDRESS(ADC_BASE + ADC_CLKDIV) |= div;

	// Enable Writing
	AT_ADDRESS(ADC_BASE + CTRL) &= ~ (0x01<<2);
	AT_ADDRESS(ADC_BASE + CTRL) |= (0x01<<2);
	
	// Setting Mode to SW Enabled Continuous
	AT_ADDRESS(ADC_BASE + STEPCONFIG1) &= ~ (0x03);
	AT_ADDRESS(ADC_BASE + STEPCONFIG1) |= (0X01);

	// To Store Step ID Number in FIFO
	AT_ADDRESS(ADC_BASE + CTRL) |= 0x01;

	return 1;
}
