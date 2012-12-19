/*
 * @FileName: Abstraction.h
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
 * @Date: 2012年02月08日星期三20:48:58
 * 
 */ 
#ifndef _ABSTRACTION_H_
#define _ABSTRACTION_H_

class AbstractionImp;

class Abstraction
{
public:
	virtual ~Abstraction();
	virtual void Operation() = 0;
	Abstraction();
private:
	
};

class RefinedAbstraction:public Abstraction
{
public:
	RefinedAbstraction(AbstractionImp* imp);
	~RefinedAbstraction();
	void Operation();
private:
	AbstractionImp* _imp;
};
#endif
