/**
 * \file ctplugin.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年11月11日星期日20:45:55
 * 
 * discript your detail info.
 */ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>				/* for dlopen */

#include <Jlog.h>

#include "ctplugin.h"

ct_plugin_st *ct_plugin_create(const char *name, const char *path)
{
	ASSERT(name != NULL && path != NULL, NULL);
	ct_plugin_st *pplugin = NULL;

	pplugin = (ct_plugin_st *)malloc(sizeof(ct_plugin_st));
	if(pplugin == NULL)
	{
		WRITELOG("malloc plugin struct failed!");
		return NULL;
	}
	
	snprintf(pplugin->name, CT_PLUGIN_NAME_LEN, "%s", name);
	snprintf(pplugin->path, CT_PLUGIN_PATH_LEN, "%s", path);
	
	pplugin->dlhandler = dlopen(path, RTLD_LAZY);		
	if(pplugin->dlhandler == NULL)
	{
		WRITELOG("open [%s] failed!", path);
		goto FAILED_EXIT;
	}
	/* TODO load function */	
	pplugin->init = dlsym(pplugin->dlhandler, "init");
	pplugin->process = dlsym(pplugin->dlhandler, "process");
	pplugin->close = dlsym(pplugin->dlhandler, "close");

	return pplugin;

FAILED_EXIT:
	if(pplugin){
		ct_plugin_destroy(pplugin);	
	}

	return NULL;
}

void ct_plugin_destroy(ct_plugin_st *pplugin)
{
	if(pplugin != NULL)	
	{
		dlclose(pplugin->dlhandler);
		free(pplugin);
	}
}


int main(int argc, char *argv[])
{
	ct_plugin_st *calc = NULL;	
	ct_plugin_st *wel = NULL;
	
	calc = ct_plugin_create("calc", "./plugs/libcalc.so");
	if(calc == NULL)
	{
		WRITELOG("create calc failed!");
		return -1;
	}

	calc->init();
	calc->process();
	calc->close();
	
	wel = ct_plugin_create("wel", "./plugs/libwel.so");
	if(wel == NULL)
	{
		WRITELOG("create wel failed!");
		return -1;
	}

	wel->init();
	wel->process();
	wel->close();

	int i = 0;	
	for(i = 0; i < 10; i++)
	{
		if(i%2)
			wel->process();
		else
			calc->process();
	}

	ct_plugin_destroy(calc);
	ct_plugin_destroy(wel);

	return 0;
}

