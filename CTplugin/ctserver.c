/**
 * \file ctserver.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年11月11日星期日21:40:34
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <Jlog.h>

#include "ctplugin.h"
#include "../CTINI/ctini.h"
#include "../XHASH/xhash.h"

#define MAX_TMP_BUFFER_SIZE		(128)

/* 读取配置文件 */
ctini_st *ct_load_config(const char *config_path)
{
	ASSERT(config_path != NULL, NULL);

	ctini_st *ctcfg= ctini_init(config_path);
	if(crcfg==  0)
	{
		WRITELOG("load config file failed!");
		return NULL;
	}
	
	return  ctcfg;	
}

hash_table_st *ct_load_plug(ctini_st *pcfg)
{
	ASSERT(pcfg != NULL, NULL);	
	
	int i = 0;
	int ret = 0;
	int total = 0;
	char plugintag[MAX_TMP_BUFFER_SIZE] = {'\0'};
	char pluginname[MAX_TMP_BUFFER_SIZE] = {'\0'};
	char pluginpath[MAX_TMP_BUFFER_SIZE * 2] = {'\0'};
	hash_table_st *ptable = NULL;
	ptable = hash_init(NULL, ct_plugin_destroy);
	
	ret = ctini_get_value(pcfg, "pluginsum", 
						 "total", &pluginbuffer);
	if(ret != 0)
	{
		WRITELOG("read plugin number failed!");
		goto FAILED_EXIT;
	}

	total = atoi(pluginbuffer);
	for(i = 0; i < total; i++)
	{
		ct_plugin_st *pplugin = NULL;
		/* get plugin name */
		snprintf(plugintag, MAX_TMP_BUFFER_SZIE, 
					"PLUGIN%d", i);
		ret = ctini_get_value(pcfg, plugintag, "name", &pluginname);
		if(ret < 0){
			WRITELOG("get plugin name failed!");	
			goto FAILED_EXIT;
		}

		ret = ctini_get_value(pcfg, plugintag, "path", &pluginpath);
		if(ret < 0){
			WRITELOG("get plugin path failed!");	
			goto FAILED_EXIT;
		}
		
		pplugin = ct_plugin_create(pluginname, pluginpath);
		if(pplugin == NULL){
			WRITELOG("pplugin create failed!");
			goto FAILED_EXIT;
		}
		/* insert into hash */
		ret = hash_insert(ptable, pplugin->name, strlen(pplugin->name),
							pplugin);
		if(ret != 0){
			WRITELOG("insert the new plugin failed!");	
			goto FAILED_EXIT;
		}
	}
	
	return ptable;
FAILED_EXIT:
	
	if(ptable != NULL)
	{
		hash_destroy(ptable);
		ptable = NULL;
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	int ret 		= 0;
	int i 			= 0;

	ctini_st *pctcfg = NULL;
	hash_table_st *pplugins = NULL;

	pctcfg = ct_load_config("./tmp.txt");
	if(pctcfg == NULL)
	{
		WRITELOG("init config failed!");
		return -1;
	}
	/* init the plugin table */
	pplugins = ct_load_plug(pctcfg);
	if(pplugins == NULL)
	{
		WRITELOG("init plugs failed!");
		return -1;
	}
	/* TODO init the epoll listener, begin to work  */

	return 0;
}

