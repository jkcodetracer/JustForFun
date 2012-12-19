/**
 * \file ctplugin.h
 * \author  wzj
 * \brief 
 	plug module
 * \version 
 * \note  
 * \date: 2012年11月11日星期日20:46:01
 * 
 * discript your detail info.
 */ 

#ifndef _CTPLUGIN_H__
#define _CTPLUGIN_H__

#define CT_PLUGIN_NAME_LEN	(128)
#define CT_PLUGIN_PATH_LEN	(256)

/* simple plugin module */
typedef struct _ct_plugin_st{
	char name[CT_PLUGIN_NAME_LEN];				/* plugin name */
	char path[CT_PLUGIN_PATH_LEN];				/* plugin path name */

	void *dlhandler;							/* dlopen handler */

	int (*init)();								/* the env */
	int (*process)();							/* main dealer */
	int (*close)();
		
	void *data;
}ct_plugin_st;

/**
 * \brief creat a new plugin 
 * \alarm get a new ct_plugin_st, please free it with the 
 * ct_plugin_destroy()
 */
ct_plugin_st *ct_plugin_create(const char *name ,const char *path);

/**
 * \brief destroy a plugin struct
 */
void ct_plugin_destroy(ct_plugin_st *pplugin);

#endif
