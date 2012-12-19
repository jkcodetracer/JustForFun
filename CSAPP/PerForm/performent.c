/*
 * @FileName: performent
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
 * @Date: 2012年04月01日星期日07:17:47
 * 
 */ 
#include<stdio.h>

int main()
{
	int i = 0;
	int pA,pB,pC;
	int ret = 0;
	int mod = 0;
	int lastmod = -1;

	for(i = 0; i < 2048; i ++)
	{
		pA = 60 + 35 * i;
		pB = 136 + 4 * i;
		pC = 157 + 1.25 * i;
		
		mod = 1;
		ret = pA;
		if(ret > pB)
		{
			ret = pB;
			mod = 2;
		}
		if(ret > pC)
		{
			ret = pC;
			mod = 3;
		}
		if(lastmod == mod)
		{
			continue;
		}

		switch(mod)
		{
			case 1:
				printf("n=%d 60+35n\n",i);
				break;
			case 2:
				printf("n=%d 136+4n\n",i);
				break;
			case 3:
				printf("n=%d 157+1.25n\n",i);
				break;
		}
		lastmod = mod;
	}
	return 0;
}

