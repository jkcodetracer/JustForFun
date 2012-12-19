/*
 * @FileName: see_struct.c
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
 * @Date: 2012年06月13日星期三23:53:13
 * 
 */ 
#include<stdio.h>

class multi{
public:
	int head;
	char my;
	char you;
	char joker[12];
	short len;
	int array[5];
	char end;

	multi():head(1){}
	
	int pren()
	{
		printf("ddd");
		return 0;
	}
};

void
dump_func(multi *m, int ti)
{
	char *t = "sdf";

	t[1] = 'b';

}

int
main()
{
	/*struct multi m = {.head = 1,
					  .my = 'a',
					  .you = 'b',
					  .joker = "abcdef",
					  .len = 20,
					  .array = {1,2,3,4,5},
					  .end = 'e'};
					  */
	multi m ;//= {1, 'a', 'b', "abcdef", 20, {1,2,3,4,5}, 'e'};
	dump_func(&m, 12);	

	return 0;
}
