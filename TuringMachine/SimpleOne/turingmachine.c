/**
 * \file turingmachine.c
 * \author  wzj
 * \brief 
 	1. A simple Turing machine.
 * \version 
 * \note  
 * \date: 2012年11月17日星期六21:10:47
 * 
 * discript your detail info.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int 	*tape;					/* 输入的纸带 */
int 	tape_len;			
int 	tape_pos 	= 0;

#define START		0
#define ACCEPT		1
#define REJECT		2
#define BLANK		0

int 	stat 		= START;	/* 当前状态 */
int 	max_stat	= 3;		/* stat number */ 
int 	max_char	= 1;		/* ?? */

typedef struct {
	int stat_now;
	int char_now;

	int stat_next;
	int char_next;
	int dir;
}rule_t;
rule_t *rule;
int rule_len;

static void init_turing(const char *program)
{
	FILE 	*f;
	char	s[100]; 
	char	s2[100];
	int 	rule_alloc_len;

	tape_len = 1024*1024;
	tape = (int*) malloc(sizeof(*tape)*tape_len);
	/**< 分配规则空间 */
	rule_len = 0;
	rule_alloc_len = 100;
	rule = (rule_t*)malloc(sizeof(rule_t) * rule_alloc_len);

	/* 读取turing规则 */
	f = fopen(program, "r");
	while(1){
		if(fgets(s, sizeof(s), f) == NULL)	
			break;
		if(sscanf(s, "%s", s2) != 1)
			continue;
		if(strcmp(s2, "tape_len") == 0)
		{
			sscanf(s, "%s%d", s2, &tape_len);	
			tape = (int *)realloc(tape, sizeof(*tape) *tape_len);
			continue;
		}
		
		if(strcmp(s2, "max_stat") == 0){
			sscanf(s, "%s%d", s2, &max_stat);	
			continue;
		}
		
		if(strcmp(s2, "max_char") == 0){
			sscanf(s, "%s%d", s2, &max_char);
			continue;
		}

		if(sscanf(s, "%d %d %d %d %d", 
				&rule[rule_len].stat_now,
				&rule[rule_len].char_now,
				&rule[rule_len].stat_next,
				&rule[rule_len].char_next,
				&rule[rule_len].dir) == 5){
			if(max_char < rule[rule_len].char_now)			
				max_char  = rule[rule_len].char_now;
			if(max_char < rule[rule_len].char_next)
				max_char  = rule[rule_len].char_next;
			if(max_stat < rule[rule_len].stat_now)
				max_stat = rule[rule_len].stat_now;
			if(max_stat < rule[rule_len].stat_next)
				max_stat = rule[rule_len].stat_next;

			printf("[%d %d %d %d %d]\n", rule[rule_len].stat_now,
					rule[rule_len].char_now,
					rule[rule_len].stat_next,
					rule[rule_len].char_next,
					rule[rule_len].dir);
			
			rule_len++;
			if(rule_len >= rule_alloc_len) {
				rule_alloc_len += 100;	
				rule = (rule_t*)realloc(rule, sizeof(rule_t)*rule_alloc_len);
			}
		}
	} 

	rule = (rule_t *) realloc(rule, sizeof(rule_t) * rule_len);
	fclose(f);
	} 
/* 初始化输入 */
static void init_tape(void)
{
	int i;
	int x;

	memset(tape, 0, sizeof(int)*tape_len);
	i = 0;
	while(1){
		if(scanf("%d", &x) != 1)	
			break;
		if(x < 0 || x > max_char)
			fprintf(stderr, "%s:%d:input error\n", __FILE__, __LINE__);
		else
			tape[i++] = x;
	}
}

static int work_turing(void)
{
	int i = 0;

	init_tape();

	while(1){
		for(i = 0; i < rule_len; i++)	
			if((rule[i].stat_now == stat) &&
				(rule[i].char_now == tape[tape_pos]))
				break;
		/* 没有找到 */
		if(i >= rule_len){
			fprintf(stderr, "%s:%d: ERROR RULES: stat=%d, char=%d\n\n", 
					__FILE__, __LINE__, stat, tape[tape_pos]);	
			exit(1);
		}
		/* 更新状态 */
		stat = rule[i].stat_next;
		tape[tape_pos] = rule[i].char_next;
		printf("[i=%d][%d]stat:[%d] tape:[%d]\n", i, tape_pos,stat, tape[tape_pos]);

		if(rule[i].dir)
			tape_pos++;
		else
			tape_pos--;

		if(stat <= REJECT)
			break;
	}

	return stat;
}

int main(int argc, char **argv)
{
	int ret;
	int i = 0;

	init_turing(argv[1]);
	ret = work_turing();
	switch(ret){
		case ACCEPT:
			printf("RESULT: ACCEPT!\n");
			break;
		case REJECT:
			printf("RESULT:REJECT !\n");
			break;
		default:
			printf("%s:%d:ret = %d\n", __FILE__, __LINE__, ret);
			break;
	}

	for(i = 0 ; i < 14; i++)
		printf("%d ", tape[i]);
	
	printf("\n");

	return 0;
}

