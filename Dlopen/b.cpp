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

class b: public baseClass{
public:
	void test()
	{
		std::cout << "in b" << std::endl;
	}
};

extern "C" baseClass* create() {
	return new b;
}

extern "C" void destroy(baseClass* p) {
	delete p;
}
