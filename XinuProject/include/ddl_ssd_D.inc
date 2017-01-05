case '1':
	AT_ADDRESS(GPIO_0 + GPIO_DATAOUT) |=(1<<15);
	break;
case '0':
	AT_ADDRESS(GPIO_0 + GPIO_DATAOUT) &= (0xFFFFFFFF ^ (1 << 15));
	break;
