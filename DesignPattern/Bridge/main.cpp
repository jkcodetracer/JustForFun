/*
 * @FileName: main.cpp
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
 * @Date: 2012年02月08日星期三21:18:37
 * 
 */ 
#include "Abstraction.h"
#include "AbstractionImp.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	AbstractionImp* imp = new ConcreteAbstractionImpA();
	Abstraction* abs = new RefinedAbstraction(imp);
	abs->Operation();

	return 0;
}
