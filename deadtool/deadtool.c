/**
 * \file deadtool.c
 * \author  wzj
 * \brief 
 *	collect the death info of the current program
 * \version 
 * \note  
 * \date: 2013年07月18日星期四23:04:08
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>

#include <Jlog.h>

#define MAX_DATA_BUFFER_SZ	(4096)
#define MAX_PATH_BUFFER_SZ	(256)

int make_dir(char *dir, char *fa_dir, char *child_dir)
{
	return 0;	
}

int make_path(char *path, int path_len, char *dir, char *file_name)
{
	int ret = 0;
	
	ret = snprintf(path, path_len, "%s/%s", dir, file_name);
	if (ret < 0 || ret >= path_len) {
		printf("string overflow!\n");	
		return -1;
	}

	return 0;
}

int file_dump(char *src_path)
{
	if ( src_path == NULL)	
		return -1;

	int ret = 0;
	FILE* src_fd = NULL, *dst_fd = NULL;
	char tmp_path[MAX_PATH_BUFFER_SZ] = {'\0'};
	char d_buffer[MAX_DATA_BUFFER_SZ] = {'\0'};

	ret = make_path(tmp_path, MAX_PATH_BUFFER_SZ, "./test", basename(src_path));
	if (ret != 0) {
		printf("makdir failed! [%s]\n", src_path);	
		return 0;
	}

	src_fd = fopen(src_path, "r");
	if (src_fd == NULL) {
		printf("open [%s] failed!\n", src_path);	
		ret = -1;
		goto ERROR_EXIT;
	}

	dst_fd = fopen(tmp_path, "w+");
	if (dst_fd == NULL) {
		printf("creat [%s] failed![%d][%s]\n", tmp_path, errno, strerror(errno));	
		ret = -1;
		goto ERROR_EXIT;
	}

	while(fgets(d_buffer, MAX_DATA_BUFFER_SZ, src_fd) != NULL) {
		fprintf(dst_fd, "%s", d_buffer);
	}
			
ERROR_EXIT:
	if (dst_fd != NULL) {
		fclose(dst_fd);	
	}
	if (src_fd != NULL) {
		fclose(src_fd);	
	}

	return ret;
}

int tranvers_dir(char *root_dir)
{
	if (root_dir == NULL) {
		return -1;	
	}

	int ret = 0;
	DIR *pdir = NULL;	
	struct dirent c_entry;
	struct dirent *p_entry = NULL;
	char *path_buffer = NULL;

	pdir = opendir(root_dir);
	if (pdir == NULL) {
		printf("open dir [%s] failed!\n", root_dir);	
		goto EXIT;
	}

	path_buffer = (char *) calloc(1, sizeof(char) * MAX_PATH_BUFFER_SZ);
	if (path_buffer == NULL) {
		printf("malloc path buffer failed!\n");	
		goto EXIT;
	}

	do {
		ret = readdir_r(pdir, &c_entry, &p_entry);	
		if (ret != 0 || p_entry == NULL) {
			break;
		}
		
		if (!strcmp(p_entry->d_name, ".") ||
			!strcmp(p_entry->d_name, "..") ) {
			continue;		
		}	
		
		if (p_entry->d_type == DT_DIR) {
			ret = make_path(path_buffer, MAX_PATH_BUFFER_SZ, root_dir, p_entry->d_name);
			if (ret != 0) {
				printf("make dir failed!\n");
				goto EXIT;	
			}
			tranvers_dir(path_buffer);
			printf("%s\n", path_buffer);
		} else if (	p_entry->d_type == DT_REG || 
					p_entry->d_type == DT_UNKNOWN){
			ret = make_path(path_buffer, MAX_PATH_BUFFER_SZ, root_dir, p_entry->d_name);
			if (ret != 0) {
				printf("make path failed!\n");
				goto EXIT;	
			}
			ret = file_dump(path_buffer);
			if (ret != 0) {
				printf("dump %s failed!\n", path_buffer);
			}
		}
	}while(1);

EXIT:
	if (pdir != NULL) {
		closedir(pdir);	
		pdir = NULL;
	}
	SAFE_FREE(pdir);	

	return 0;
}

void dead_dump()
{
	int ret = 0;
	pid_t c_pid = getpid();
	char *proc_dir = NULL;

	proc_dir = (char *)calloc(1, sizeof(char) * MAX_PATH_BUFFER_SZ);
	if (proc_dir == NULL) {
		printf("malloc proc_dir failed!\n");
		return ;
	}	

	ret = snprintf(proc_dir, MAX_PATH_BUFFER_SZ, "/proc/%d", c_pid);
	if (ret < 0 || ret >= MAX_PATH_BUFFER_SZ) {
		printf("make proc dir failed!\n");	
		goto EXIT;
	}
	/* 遍历proc文件夹 */
	ret = tranvers_dir(proc_dir);
	if (ret < 0) {
		printf("tranverse dir failed!\n");	
		goto EXIT;
	}

EXIT:
	SAFE_FREE(proc_dir);
}

int main(int argc, char *argv[])
{
	dead_dump();	

	return 0;
}

