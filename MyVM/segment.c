/**
 * \file segment.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年09月15日星期六16:48:15
 */ 
#include <stdio.h>
#include <stdlib.h>
#include "../Jlog.h"

/**
 * 段描述符
 */
typedef struct _segment_descriptor_st{
	/* 一共两个双字, 4个字节 */
	int segment_limit;		/* 段限长， 总共20bit, 具体值取决于粒度标记G
	如果G＝0, limit范围从1B到1MB, 如果G＝1, 则段长度limit范围可以从4k到4G*/		
	int B;					/* 默认大小, B=0 对应的segment_linit为16位的,
	也就是上限为0xFFFF, 如果B＝1， 那么对应的segment_limit为32位的， 
	也就是上限为0XFFFF FFFF */
	int E;					/* 堆栈的扩展放方向， E=0,向上扩展， 逻辑地址中的
	偏移范围从0～limit, E=1,向下扩展, 偏移范围从limit 到 0XFFFF FFFF 或0xFFFF*/					
	int base;				/* 基地址 32bit, 定义了在4GB线性地址空间中一个段字节
	0所处的位置. 这个地址一般会对齐16字节边界 */	
	int type;				/* 段类型字段, 4bit,  */
	int S;					/* S=0 系统段描述符号， S＝1代码/数据描述符号 */
	int DPL; 				/* 特权级别 2bit, 4个级别 */
	int P;					/* segment present, 该段是否在内存中, 1在. 0,不在 */		
	int reserve;
}segment_descriptor_st;

/**
 * 段描述符表
 * GDT/LDT/IDT
 */
typedef struct _sd_table_st{
	segment_descriptor_st **psd;	/* 描述符表 */

	int table_len;
}sd_table_st;
/**
 * 段选择符
 */
typedef struct _sd_selector_st{
	int RPL;			/* requested provilege level */	
	int TI;				/* 标记选择全局还是局部sd_table */
	int index;			/* 索引值 */
}sd_selector_st;

/**
 * 段寄存器
 */
typedef struct _sd_registor_st{
	/* 这里是可见部分, 提供给编程者使用 */
	sd_selector_st selector;	/* 段选择符号 */	
	/* 以下是隐藏部分, 仅对cpu可见,加快寻址速度 */
	int base;					/* 段的基地址 */
	int limit;					/* 段的长度限制 */
	int attribute;				/* 段的访问属性 */
}sd_registor_st;


int sd_init(sd_table_st *ptable)
{
	int i = 0;
	ASSERT(ptable != NULL, -1);	
	
	ptable->psd = (segment_descriptor_st**)malloc(20 * sizeof(segment_descriptor_st*));
	if(ptable->psd == NULL)
	{
		WRITELOG("malloc sd failed!");
		return -1;
	}

	ptable->table_len = 20;

	for(i = 0; i < ptable->table_len; ++i)
	{
		ptable->psd[i] = (segment_descriptor_st*) malloc(sizeof(segment_descriptor_st));
		if(ptable->psd[i] == NULL)
		{
			WRITELOG("malloc one segment_descriptor_st failed!");
			return -1;
		}
		memset(ptable->psd[i], 0, sizeof(segment_descriptor_st));
	}

	WRITELOG("malloc all 20 segment_descriptor_st success!");

	for(i = 0; i < ptable->table_len; ++i)
	{
		segment_descriptor_st* psd = ptable->psd[i];	

		psd->segment_limit = 128;

	}

	return 0;
}




int main(int argc, char *argv[])
{
	
}
