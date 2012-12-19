/*
 * @FileName: a.cpp
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
 * @Date: 2012年02月07日星期二23:55:10
 * 
 */ 
#include "base.h"
#include <cmath>
#include <iostream>

class a: public baseClass{
public:
	void test()
	{
		std::cout << "in a" << std::endl;
	}
};

extern "C" baseClass* create() {
	return new a;
}

extern "C" void destroy(baseClass* p) {
	delete p;
}
