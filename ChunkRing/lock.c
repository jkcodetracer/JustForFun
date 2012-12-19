/**
 * \file lock.c
 * \author  wzj
 * \brief  try the lock free.
 * \version 
 * \note  
 * \date: 2012年08月23日星期四21:11:40
 */ 

#include <stdio.h>
#include <unistd.h>

inline int CAS(unsigned long *mem, unsigned long new_val, unsigned long old_val)
{
	__typeof (*mem) ret;
	__asm __volatile (
		"lock; cmpxchgl %2, %1"	
		:"=a" (ret), 	//0
	 	 "=m" (*mem)	//1
		:"r"(new_val), 	//2
		 "m" (*mem), 	//3
		 "0"(old_val)	//4
		);
	return (int)ret;
#if 0
	__asm __volatile (
		"lock; cmpxchgl %1, %2"
		: "=a" (*mem)
		:"r"(new_val), "0"(old_val)
			);
	return 0;
#endif
}

int main()
{
	unsigned long next = 1333;
	unsigned long target = 123;
	unsigned long old = 3333;

	printf("CAS: %d\n", CAS(&next, target, old));
	printf("next: %d target: %u\n", next, target);
	old = next;
	printf("CAS: %d\n", CAS(&next, target, old));
	printf("next: %d target: %u\n", next, target);
	
	return 0;
}
#if 0
__typeof (*mem) ret;
__asm __volatile(
	"lock; cmpxchgl %2, %1"
	:"=a"(ret),
	 "=m"(*mem)
	:"r" (new_val),
	 "m" (*mem)
	 "0" (old_val)
	);
#endif
