/*
 * @FileName: code.c
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
 * @Date: 2012年06月10日星期日22:00:27
 * 
 */ 
int accum = 0;

int sum(int x, int y)
{
	int t = x + y;

	accum += t;
	return t;
}
