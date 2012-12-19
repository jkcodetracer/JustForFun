/*
 * @FileName: AbstractionImp.h
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
 * @Date: 2012年02月08日星期三20:54:06
 * 
 */ 
#ifndef _ABSTRACTIONIMP_H
#define _ABSTRACTIONIMP_H

class AbstractionImp
{
public:
	virtual ~AbstractionImp();
	virtual void Operation() = 0;
protected:
	AbstractionImp();
private:

};

class ConcreteAbstractionImpA:public AbstractionImp
{
public:
	ConcreteAbstractionImpA();
	~ConcreteAbstractionImpA();
	virtual void Operation();
private:
};

class ConcreteAbstractionImpB: public AbstractionImp
{
public:
	ConcreteAbstractionImpB();
	~ConcreteAbstractionImpB();
	virtual void Operation();
private:
};

#endif
