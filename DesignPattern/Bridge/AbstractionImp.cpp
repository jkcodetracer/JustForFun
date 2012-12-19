/*
 * @FileName: AbstractionImp.cpp
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
 * @Date: 2012年02月08日星期三21:11:01
 * 
 */ 
#include "AbstractionImp.h"
#include<iostream>

using namespace std;

AbstractionImp::AbstractionImp()
{

}

AbstractionImp::~AbstractionImp()
{
	
}

void AbstractionImp::Operation()
{
	cout << "AbstractionImp...imp..." << endl;
}

ConcreteAbstractionImpA::ConcreteAbstractionImpA()
{
}

ConcreteAbstractionImpA::~ConcreteAbstractionImpA()
{

}

void ConcreteAbstractionImpA::Operation()
{
	cout << "ConctreteAbstractionImpA..." << endl;
}

ConcreteAbstractionImpB::ConcreteAbstractionImpB()
{
}

ConcreteAbstractionImpB::~ConcreteAbstractionImpB()
{

}

void ConcreteAbstractionImpB::Operation()
{
	cout << "ConcreteAbstractionImpB..." << endl;
}

