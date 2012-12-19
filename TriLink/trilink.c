/**
 * \file trilink.c
 * \author  wzj
 * \brief  连连看...
 * \version  1.0
 * \note  
 * \date  2012年09月09日星期日19:05:32
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_INIT_CHR	(' ')

typedef struct _block_area_st{
	char block[10][10];
	int normal_size;
	int size;
}block_area_st;

typedef struct _point_st{
	int x;
	int y;
}point_st;


int area_init(block_area_st *area)
{
	memset(area, DEFAULT_INIT_CHR, sizeof(*area));
	
	area->size = 10;
	area->normal_size = 8;

	return 0;
}

void area_show(block_area_st *area)
{
	int i = 0, j = 0;

	for(i = 0; i < area->size; ++i)
	{
		for(j = 0; j < area->size; ++j)
			printf("%c ", area->block[i][j]);
		printf("\n");
	}
}

int area_random_fulfil(block_area_st *area)
{
	int x, y, i;
	int total = (area->normal_size) * (area->normal_size) >> 1;
srandom(time(NULL));
	
	for(i = 0; i < total; ++i)	
	{
		int tmp_count = 0;
		char tmp_chr = random()%7 + 'a';
		while(1)		
		{
			x = random()%area->normal_size + 1;	
			y = random()%area->normal_size + 1;
			if(area->block[x][y] == DEFAULT_INIT_CHR)
			{
				tmp_count++;	
				area->block[x][y] = tmp_chr;
			}

			if(tmp_count >= 2)
				break;
		}
	}
	
	return 0;
}

int case_same_line(block_area_st *area, point_st *a, point_st *b)
{
	int ret = -1;	
	/* 同一条线 */
	while(a->x == b->x)
	{
		int i = 0, j = 0;
		for(i = a->y; i <= b->y; ++i)	
		{
			if(area->block[i][a->x] != DEFAULT_INIT_CHR)	
				break;		
		}

		if(i > b->y)
		{
			ret = 0;
			break;
		}
		/* 向右 */
		for(j = a->x; j <= area->size - 1; ++j)
		{
			int m = 0;
			if(area->block[a->y][j] != DEFAULT_INIT_CHR ||
			   area->block[b->y][j] != DEFAULT_INIT_CHR)	
				break;

			for(m = a->y; m <= b->y; ++m)
			{
				if(area->block[m][j] != DEFAULT_INIT_CHR)	
					break;
			}

			if(m > b->y)
				return 0;
		}

		/* 向左 */	
		for(j = a->x; j >= 0; --j)
		{
			int m = 0;	
			if(area->block[a->y][j] != DEFAULT_INIT_CHR ||
			   area->block[b->y][j] != DEFAULT_INIT_CHR)
			   	break;

			for(m = a->y; m <= b->y; ++m)
			{
				if(area->block[m][j] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->y)
				return 0;
		}

		break;
	}
	/* 另一种情况 */
	while(a->y == b->y)
	{
		int i, j;	
		for(i = a->x; i <= b->x; ++i)
		{
			if(area->block[a->y][i] != DEFAULT_INIT_CHR)	
				break;
		}

		if(i > b->x)
		{
			ret = 0;
			break;
		}

		for(j = a->y; j <= area->size-1; ++j)
		{
			if(area->block[j][a->x] != DEFAULT_INIT_CHR ||
			   area->block[j][b->x] != DEFAULT_INIT_CHR)
				break;
			int m = 0;
			for(m = a->x; m <= b->x; ++m)
			{
				if(area->block[j][m] != DEFAULT_INIT_CHR)	
					break;
			}

			if(m > b->x)
				return 0;
		}

		for(j = a->y; j >= 0; --j)
		{
			if(area->block[j][a->x] != DEFAULT_INIT_CHR ||
			   area->block[j][b->x] != DEFAULT_INIT_CHR)
				break;
			int m = 0;
			for(m = a->x; m <= b->x; ++m)
			{
				if(area->block[j][m] != DEFAULT_INIT_CHR)
					break;
			}
			
			if(m > b->x)
				return 0;
		}

		break;
	}

	return ret;
}
int case_A_down(block_area_st *area, point_st *a, point_st *b)
{
	if(a->y <= b->y)	
		return -1;
	
	int i, j, m;
	/* 中段 */	
	for(i = a->y; i >= b->y;  --i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)	
			break;

		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}
		if(j > b->x)
		{
			for(m = i; m >= b->y; --m)
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)
					break;
			}
			if(m > b->y)
				return 0;
		}
	}
	/* 上段 继续之前的*/
	for(;i >= 0; --i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)
			break;
		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}
		if(j > b->x)
		{
			for(m = i; m <= b->y; ++m)
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)	
					break;	
			}

			if(m > b->y)
				return 0;
		}

	}

	/* 下端 */
	for(i = a->y; i < area->size-1; ++i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)
			break;

		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}

		if(j > b->x)
		{
			for(m = i; m >= b->y; --m)	
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)
					break;
			}

			if(m < b->y)
				return 0;
		}
	}

	/* 水平遍历 */
	/* middle */
	for(i = a->x; i <= b->x; ++i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)
			break;

		for(j = a->y; j >= b->y; --j)		
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}

		if(j < b->y)
		{
			for(m = i; m <= b->x; ++m)
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->x)	
				return 0;
		}
	}
	/* right */
	for(; i < area->size - 1; ++i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)
			break;

		for(j = a->y; j >= b->y; --j)
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}

		if(j < b->y)
		{
			for(m = i; m >= b->x; --m)
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m < b->x)
				return 0;
		}
	}
	/*left*/
	for(i = a->x - 1; i >= 0; --i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)		
			break;

		for(j = a->y; j >= b->y; --j)
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}

		if(j < b->y)
		{
			for(m = i; m <= b->x; ++m)	
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->x)
				return 0;
		}
	}

	return -1;
}

int case_A_up(block_area_st *area, point_st *a, point_st *b)
{
	if(a->y >= b->y)
		return -1;
	
	int i, j, m;
	/* 中段 */
	for(i = a->y; i <= b->y; ++i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)
			break;

		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}
		if(j > b->x)
		{
			for(m = i; m <= b->y; ++m)	
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->y)
				return 0;
		}
	}
	/*下段 继续之前的*/
	for(;i < area->size-1; ++i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)	
			break;
		
		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}
		if(j > b->x)
		{
			for(m = i; m >= b->y; --m)	
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)
					break;
			}

			if(m < b->y)
				return 0;
		}
	}
	/* 上端 */
	for(i = a->y; i >= 0; --i)
	{
		if(area->block[i][a->x] != DEFAULT_INIT_CHR)
			break;

		for(j = a->x; j <= b->x; ++j)
		{
			if(area->block[i][j] != DEFAULT_INIT_CHR)
				break;
		}

		if(j > b->x)
		{
			for(m = i; m <= b->y; ++m)
			{
				if(area->block[m][b->x] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->y)
				return 0;
		}
	}

	/* 水平遍历  */
	/* middle*/
	for(i = a->x; i <= b->x; ++i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)
			break;

		for(j = a->y; j <= b->y; ++j)
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}

		if(j > b->y)
		{
			for(m = i; m <= b->x; ++m)	
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->x)
				return 0;
		}
	}

	/* right */
	for(; i < area->size - 1; ++i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)
			break;

		for(j = a->y; j <= b->y; ++j)
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}
		
		if(j > b->y)
		{
			for(m = i; m >= b->x; --m)
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m < b->x)
				return 0;
		}
	}

	/*left*/	
	for(i = a->x - 1; i >= 0; --i)
	{
		if(area->block[a->y][i] != DEFAULT_INIT_CHR)	
			break;

		for(j = a->y; j <= b->y; ++j)
		{
			if(area->block[j][i] != DEFAULT_INIT_CHR)
				break;
		}

		if(j > b->y)
		{
			for(m = i; m <= b->x; ++m)
			{
				if(area->block[b->y][m] != DEFAULT_INIT_CHR)
					break;
			}

			if(m > b->x)
				return 0;
		}
	}
	
	return -1;
}

int case_diff_line(block_area_st *area, point_st *a, point_st *b) 
{	
	int ret = -1;

	ret = case_A_up(area, a, b);
	if(ret == 0)
		return ret;
	
	ret = case_A_down(area, a, b);
	if(ret == 0)
		return ret;
	
	return ret;
}

int area_judge(block_area_st *area, point_st *a, point_st *b)
{
	int ret = 0;
	point_st *tmp = NULL;
	char original_chr_A = area->block[a->y][a->x];
	char original_chr_B = area->block[b->y][b->x];
	
	if(original_chr_A != original_chr_B)
	{
		printf("no equal.\n");
		return -1;
	}
	
	/* 假设成立 */
	area->block[a->y][a->x] = DEFAULT_INIT_CHR;
	area->block[b->y][b->x] = DEFAULT_INIT_CHR;

	/* 获取较左边，较上面的点,指定为a */
	if( a->x > b->x) 
	{
		tmp = a;
		a = b;
		b = tmp;
	}

	if((a->x == b->x) || (a->y == b->y))
	{
		ret = case_same_line(area, a, b);	
		if(ret == 0)
		{
			printf("OK\n");
			return 0;
		}
	}

	ret = case_diff_line(area, a, b);
	if(ret == 0)
	{
		printf("OK2 \n");
		return 0;
	}

	area->block[a->y][a->x] = original_chr_A;
	area->block[b->y][b->x] = original_chr_B;
	return -1;
}

int main(int argc, char *argv[])
{
	block_area_st area;
	point_st a;
	point_st b;

	area_init(&area);	
	area_random_fulfil(&area);
	area_show(&area);
	
	while(1)	
	{
		scanf("%d,%d %d,%d", &(a.x), &(a.y), &(b.x), &(b.y));

		printf("%d,%d %d,%d\n", a.x, a.y, b.x, b.y);

		area_judge(&area, &a, &b);

		area_show(&area);
	}

	return 0;
}


