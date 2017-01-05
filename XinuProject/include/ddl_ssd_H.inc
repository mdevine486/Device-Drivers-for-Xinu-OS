case '1':
	AT_ADDRESS(GPIO_1 + GPIO_DATAOUT) |=(1<<16);
	break;
case '0':
	AT_ADDRESS(GPIO_1 + GPIO_DATAOUT) &= (0xFFFFFFFF ^ (1 << 16));
	break;
