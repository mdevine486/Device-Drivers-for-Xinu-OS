/* ssdwrite.c - 7 Segment Writing Values */

#include <xinu.h>

devcall	ssdwrite(struct dentry* devptr, char* buff, int32 count){
	#include<ddl_ssd_dir_out.inc>
	// Write the Value
	switch(buff[0]){
		#include<ddl_ssd_A.inc>
	}
	switch(buff[1]){
		#include<ddl_ssd_B.inc>
	}
	switch(buff[2]){
		#include<ddl_ssd_C.inc>
	}
	switch(buff[3]){
		#include<ddl_ssd_D.inc>
	}
	switch(buff[4]){
		#include<ddl_ssd_E.inc>
	}
	switch(buff[5]){
		#include<ddl_ssd_F.inc>
	}
	switch(buff[6]){
		#include<ddl_ssd_G.inc>
	}
	switch(buff[7]){
		#include<ddl_ssd_H.inc>
	}
	return 1;
}
