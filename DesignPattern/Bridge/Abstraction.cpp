/*
 * @FileName: Abstraction.cpp
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
 * @Date: 2012年02月08日星期三20:59:42
 * 
 */ 
#include "Abstraction.h"
#include "AbstractionImp.h"

#include<iostream>
using namespace std;

Abstraction::Abstraction()
{
	
}
Abstraction::~Abstraction()
{
	
}

RefinedAbstraction::RefinedAbstraction(AbstractionImp *imp)
{
	_imp = imp;
}

RefinedAbstraction::~RefinedAbstraction()
{
}

void RefinedAbstraction::Operation()
{
	_imp->Operation();
}


