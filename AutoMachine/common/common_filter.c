/**
 * \file common_filter.c 
 * \author  wzj
 * \brief  a C's common filter, with the auto machine.
 * \version  
 * \note  
 * \date: 2013年04月24日星期三22:28:33
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Jlog.h>

#define MAX_COMMON_BUFFER_SIZE	(8 * 1024 * 1024)

typedef enum status_list{
	S_BEGIN,
	S_LEFT_LINE,
	S_LEFT_STAR,
	S_RIGHT_STAR,
	S_FINISH,
	S_ERROR
}status;

static int yeild_common(const char *file_path);

int main(int argc, char *argv[])
{
	if (argc <=1) {
		printf("usage: common_filter [file_path]\n");	
		return -1;
	}
	
	char *file_path = NULL;
	
	file_path = strdup(argv[1]);
	if(file_path == NULL) 
		return -1;
	
	yeild_common(file_path);

	free(file_path);
	return 0;
}

static int yeild_common(const char *file_path)
{
	if (file_path == NULL)
		return -1;

	FILE *fp = NULL;	
	char line_buffer[1024] = {'\0'};
	char *buffer = NULL;
	char *pcp = NULL;
	int embed_counter = 0;
	status c_status = S_BEGIN;

	
	fp = fopen(file_path, "r");
	if (fp == NULL) {
		printf("open file %s failed! [%s]\n", file_path, strerror(errno));	
		return -1;
	}
	
	buffer = (char *)calloc(sizeof(char), MAX_COMMON_BUFFER_SIZE);
	if (buffer == NULL) {
		printf("malloc buffer failed!\n");	
		return -1;
	}
	/* auto parser */
	pcp = buffer;
	while (fgets(line_buffer, 1024, fp) != NULL) {
		char *pb, *pe, *pc;	/* begin, end, current */			
		pb = pc = line_buffer;
		pe = NULL;

		while (*pc) {
			switch (c_status) {
				case S_BEGIN: {
					if (*pc == '/')	
						c_status = S_LEFT_LINE;
					pc++;	
					break;
				}	
				case S_LEFT_LINE: {
					if (*pc == '*')	{
						embed_counter ++;	
						c_status = S_LEFT_STAR;
					} else
						c_status = S_BEGIN;
					pc++;
					pb = pc;
					break;
				}
				case S_LEFT_STAR: {
					pe = pc;
					if (*pc == '*')	{
						pe = pc - 1;
						c_status = S_RIGHT_STAR;
					}
					pc++;
					break;
				}
				case S_RIGHT_STAR: {
					c_status = S_LEFT_STAR;
					if (*pc == '*')	{
						pe = pc - 1;
						c_status = S_RIGHT_STAR;
					}
					if (*pc == '/')
						c_status = S_FINISH;
					
					pc++;
					break;
				}	
				case S_FINISH: {
					embed_counter--; 
					if (embed_counter < 0) {
						printf ("the embed counter missing...\n");	
						exit(0);
					}
					if (embed_counter > 0) {
						pe = pc;				
						c_status = S_LEFT_STAR;
						break;
					}
					int cplen = pe-pb+1;
					if (pcp - buffer + cplen + 2 < 0) {
						printf ("the buffer is full!\n");	
						exit(-1);
					}
					memcpy(pcp, pb, cplen);	
					pcp = pcp + cplen;
					printf ("current common: \n%s\n", buffer);
					
					memset(buffer, 0, MAX_COMMON_BUFFER_SIZE);
					pcp = buffer;
					c_status = S_BEGIN;
					
					pc++;
					pb = pc;
					pe = NULL;
					break;
				}
				default: {
					printf ("parse error! %d \n", __LINE__);	
					exit(-1);
				}
			}	
		}
		if (c_status == S_LEFT_STAR ||
			c_status == S_RIGHT_STAR ||
			c_status == S_FINISH) {
			int cplen = pe - pb + 1;		
			if (pcp - buffer + cplen + 2 < 0) {
				printf ("the buffer is full!\n");	
				exit(-1);
			}
			memcpy(pcp, pb, cplen);
			pcp = pcp + cplen;

			if (c_status == S_FINISH) {
				embed_counter--;
				if (embed_counter < 0) {
					printf("embed counter missing!\n");	
					exit(-1);
				}

				if (embed_counter == 0)
				{
					printf ("current common: \n%s\n", buffer);
				}
			}
		}
	}
	
	fclose(fp);
	return 0;
}

