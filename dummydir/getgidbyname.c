/*
 * @FileName: getgidbyname.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月29日星期五06:47:46
 * 
 */ 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int
getpidbyname(const char *name)
{
	struct dirent *curdir_ent = NULL;
	DIR	*dir = NULL;
	char path[1024] = {0};
	char buf[512] = {0};
	pid_t pid = 0;
	int ret = 0;
	
	dir = opendir("/proc");
	if(dir == NULL)
	{
		printf("open failed !\n");
		return -1;
	}
	
	while((curdir_ent = readdir(dir)) != NULL)
	{
		if(curdir_ent->d_type != DT_DIR)	
		{
			continue;
		}
		if(strcmp(curdir_ent->d_name, ".") == 0 ||
			strcmp(curdir_ent->d_name, "..") == 0)
		{
			continue;
		}
		int num_flag = 1;
		char *p = curdir_ent->d_name;
		while(*p != '\0')
		{
			if(*p < '0' ||
			   *p > '9')	
			{
				num_flag = 0;
				break;
			}
			p++;
		}
		if(num_flag == 0)
		{
			continue;
		}
		int cur_pid = atoi(curdir_ent->d_name);
		snprintf(path, 1024, "/proc/%s/status", curdir_ent->d_name);
		FILE *fp = fopen(path, "r");
		if(fp == NULL)
		{
			printf("open %s failed\n", path);
			continue;	
		}

		if(fgets(buf, 512, fp) == NULL)
		{
			fclose(fp);
			continue;
		}
		fclose(fp);

		char tmp_name[128] = {0};	
		sscanf(buf, "%*s %s", tmp_name);
		if(tmp_name != NULL && tmp_name[0] != '\0')
		{
			if(strcmp(tmp_name, name) == 0)
			{
				printf("%d\n", cur_pid);
			}
		}

	}
	return 0;
}

int 
main(int argc, char *argv[])
{
	getpidbyname(argv[1]);	
}
