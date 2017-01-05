import xml.etree.ElementTree as et

tree = et.parse('../DDL/led.xml')
root = tree.getroot()
#LED ------------------------------------starts--------------------------
# LED WRITE 
text = root[0][1][3]
gpio = root[0][1][1].text
s=''
pin = root[0][1][2].text
for child in text:
	val=child.text
	s+='case '+val+':\n\t'
	if val=='0':
		s+='AT_ADDRESS(GPIO_'+gpio+' + GPIO_DATAOUT) &= (0xFFFFFFFF ^ (1 << '+pin+'));\n\tbreak;\n'
	elif val=='1':
		s+='AT_ADDRESS(GPIO_'+gpio+' + GPIO_DATAOUT) |=(1<<'+pin+');\n\tbreak;\n'

f=open('../include/ddl_led_write.inc','w')
f.write(s)
f.close()

# AT_ADDRESS(GPIO_0 + GPIO_OE) &= (0xFFFFFFFF ^ (1 << 14))
# LED DIRECTION OUT 
s = ''
s = 'AT_ADDRESS(GPIO_'+gpio+' + GPIO_OE) &= (0xFFFFFFFF ^ (1 << '+pin+'));\n\t '
f = open('../include/ddl_led_dir_out.inc','w')
f.write(s)
f.close()

#AT_ADDRESS(GPIO_0 + GPIO_OE) |=(1<<14);
# LED DIRECTION IN 
s = ''
s = 'AT_ADDRESS(GPIO_'+gpio+' + GPIO_OE) |=(1<<'+pin+');\n\t'
f = open('../include/ddl_led_dir_in.inc','w')
f.write(s)
f.close()

# (AT_ADDRESS(GPIO_0 + GPIO_DATAIN) >> 14) & 1;
#LED read 

s = ''
s = '(AT_ADDRESS(GPIO_'+gpio+' + GPIO_DATAIN) >>'+pin+') & 1;\n\t'
f = open('../include/ddl_led_read.inc','w')
f.write(s)
f.close()

#LED -------------------------ends-------------------------------------------------


##############################SSD Starts ############################################
ssdtree = et.parse('../DDL/ssd.xml')
ssdroot = ssdtree.getroot()
s1=''
# s = 'AT_ADDRESS(GPIO_'+gpio+' + GPIO_OE) &= (0xFFFFFFFF ^ (1 << '+pin+'));\n\t '
for i in range(1,9):
	 pin = int(ssdroot[0][i][1].text)
	 gpio = str(pin / 32) 
	 pin = str(pin % 32) 
	 s1 += 'AT_ADDRESS(GPIO_'+gpio+' + GPIO_OE) &= (0xFFFFFFFF ^ (1 << '+pin+'));\n'
	 text = ssdroot[0][i][2]
	 s2=''
	 for child in text:
		val=child.text
		s2 +='case '+"'"+val+"'"+':\n\t'
		if val=='0':
			s2 +='AT_ADDRESS(GPIO_'+gpio+' + GPIO_DATAOUT) &= (0xFFFFFFFF ^ (1 << '+pin+'));\n\tbreak;\n'
		elif val=='1':
			s2 +='AT_ADDRESS(GPIO_'+gpio+' + GPIO_DATAOUT) |=(1<<'+pin+');\n\tbreak;\n'
	 fl = '../include/ddl_ssd_'+ ssdroot[0][i][0].text +'.inc'
	 f = open(fl,'w')
	 f.write(s2)
	 f.close()

f = open('../include/ddl_ssd_dir_out.inc','w')
f.write(s1)
f.close()
############################## SSD Ends  #############################################


############################## TEMP SENSOR ##########################################
tmptree = et.parse('../DDL/tmp.xml')
temproot = tmptree.getroot()

s3 = 'AT_ADDRESS(ADC_BASE + FIFO0DATA) &(0xFFF);'
f  = open('../include/ddl_tmp_read.inc','w')
f.write(s3)
f.close()


	 

##############################TEMP SENSOR Ends  #############################################

