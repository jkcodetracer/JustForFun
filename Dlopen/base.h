/*
 * @FileName: base.h
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
 * @Date: 2012年02月07日星期二23:52:39
 * 
 */ 
#ifndef __BASE__
#define __BASE__

#include<iostream>

class baseClass {
public:
	virtual void test(){};
	virtual ~baseClass(){};
};

typedef baseClass* (*create_t)();
typedef void (*destroy_t)(baseClass*);

#endif
