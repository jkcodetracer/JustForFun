/**
 * \file test.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2013年12月07日星期六23:07:35
 *	for protobuf-c test 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "amessage.pb-c.h"

int main(int argc, const char *argv[])
{
	AMessage msg = AMESSAGE__INIT;
	void *buf;
	unsigned len;
	char test[1000] = {'\0'};

	msg.a = atoi(argv[1]);
	len = amessage__get_packed_size(&msg);
	
	buf = malloc(len);
	amessage__pack(&msg, buf);

	printf("%d\n", len);
	fwrite(buf, len, 1, stdout);
	
	free(buf);
	return 0;	
}


