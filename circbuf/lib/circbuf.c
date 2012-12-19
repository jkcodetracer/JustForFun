/*****************************************************************************\
*                     CircBuf - Circular Buffer FIFO's                        *
*          --------------------------------------------------------           *
*                                                                             *
* Filename : circbuf.c                                                        *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 3                     *
* of the License.                                                             *
                                                                              *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2007 Lennart Yseboodt *
\*****************************************************************************/

#include "circbuf.h"
//查看某块缓冲区的长度。
euint32 cb_ptrToSector(CircularBuffer *cb,euint8* ptr)
{
	return((ptr-(cb->buf))/(cb->sectorsize));
}

euint8* cb_sectorToPtr(CircularBuffer *cb,euint32 sector)
{
	//根据每块的大小来设定跳转多少
	return(cb->buf+(sector*(cb->sectorsize)));
}
//检查属性 
euint8 cb_getAttr(CircularBuffer *cb,euint8 attribute)
{
	return(cb->status&(1<<attribute));
}
//设置缓区的状态 val用于控制清除还是设置
void cb_setAttr(CircularBuffer *cb,euint8 attribute,euint8 val)
{	//因为读写是可以同时进行的，但是不能同时有多个读者，多个写者。
	//因此使用了置位的操作，而不是赋值的操作。
	if(val){
		cb->status|=1<<attribute;
	}else{
		cb->status&=~(1<<attribute);
	}
}
//初始化
void cb_init(CircularBuffer *cb, euint8* mem, euint32 numsectors, euint32 sectorsize)
{
	cb->buf = mem;	//获取缓冲区 
	cb->numsectors = numsectors;
	cb->sectorsize = sectorsize;
	cb->status = 0;
	cb->readPointer = 0;
	cb->writePointer = 0;
	cb_setAttr(cb,CB_BUF_WRITEONLY,1); //设置为只写的初始化状态
}
//返回READ指针头 奔放不是过错...
euint8* cb_readPacket(CircularBuffer *cb)
{	//如果r w 指针相等，并且处于非只读状态，证明缓冲区是空的...
	if((cb->readPointer == cb->writePointer)&&(!cb_getAttr(cb,CB_BUF_READONLY)))return(0);
	if(cb_getAttr(cb,CB_READ_INP))return(0); //检查缓冲区是否为正在读状态。 保证只有一个读者
	cb_setAttr(cb,CB_READ_INP,1); //设置缓冲区为正在读状态，
	return(cb_sectorToPtr(cb,cb->readPointer));
}
//读取完成调用，调整指针，调整状态
void cb_doneReadPacket(CircularBuffer *cb)
{	//这里是读的下一个状态，只有从读状态才能进入到这里。
	if(!cb_getAttr(cb,CB_READ_INP))return;
	if(cb_getAttr(cb,CB_BUF_READONLY))cb_setAttr(cb,CB_BUF_READONLY,0);
	//如果达到缓冲区的边界，就绕到开头,否则，继续
	//缓冲区是按照块来分配的，每次就只给一块，多用了的后果就是值会被覆盖
	if(cb->readPointer+1 == cb->numsectors){
		cb->readPointer=0;
	}else{
		cb->readPointer++;
	}
	//如果缓冲区空了，转到只写状态
	if(cb->readPointer == cb->writePointer)cb_setAttr(cb,CB_BUF_WRITEONLY,1);	
	//并且清除读取中的状态。
	cb_setAttr(cb,CB_READ_INP,0);	
}
//取消读取的过程
void cb_cancelReadPacket(CircularBuffer *cb)
{	//只有在读取中的状态，才有效
	if(!cb_getAttr(cb,CB_READ_INP))return;
	//清除读取中状态
	cb_setAttr(cb,CB_READ_INP,0);	
}
//这货难道支持多线程读写？原子性不能保证，比较彻
euint8* cb_writePacket(CircularBuffer *cb)
{   //写数据，先看看缓冲区满没满，才开始写
	if((cb->readPointer == cb->writePointer)&&(!cb_getAttr(cb,CB_BUF_WRITEONLY)))return(0);
	if(cb_getAttr(cb,CB_WRITE_INP))return(0); //如果已经在写状态，那么返回
	cb_setAttr(cb,CB_WRITE_INP,1);		//设置进入写状态
	return(cb_sectorToPtr(cb,cb->writePointer)); 
}
//完成写,处理指针和状态
void cb_doneWritePacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_WRITE_INP))return;
	if(cb_getAttr(cb,CB_BUF_WRITEONLY))cb_setAttr(cb,CB_BUF_WRITEONLY,0);
	//相信我，求余运算比这慢得多
	if(cb->writePointer+1 == cb->numsectors){
		cb->writePointer=0;
	}else{
		cb->writePointer++;
	}
	if(cb->readPointer == cb->writePointer)cb_setAttr(cb,CB_BUF_READONLY,1);
	cb_setAttr(cb,CB_WRITE_INP,0);	
}
//终止写
void cb_cancelWritePacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_WRITE_INP))return;
	cb_setAttr(cb,CB_WRITE_INP,0);	
}
//??...
void cb_lastPacketIsIn(CircularBuffer *cb)
{
	cb_setAttr(cb,CB_LASTIN,1);
}
//??...
euint8 cb_moreComing(CircularBuffer *cb)
{
	return((cb_getAttr(cb,CB_LASTIN))?0:1);
}
//空了?
void cb_lastPacketIsOut(CircularBuffer *cb)
{
	cb_setAttr(cb,CB_ALLREAD,1);
}
//检查是否可读
euint8 cb_readyReading(CircularBuffer *cb)
{
	return((cb_getAttr(cb,CB_ALLREAD))?1:0);
}

#ifdef DEBUG
void cb_printStatus(CircularBuffer *cb)
{
	euint8 c;

	printf("BUF READONLY      : %i\n"
		   "BUF WRITEONLY     : %i\n"
           "READ  IN PROGRESS : %i\n"
           "WRITE IN PROGRESS : %i\n",
	cb_getAttr(cb,CB_BUF_READONLY)?1:0,
	cb_getAttr(cb,CB_BUF_WRITEONLY)?1:0,
	cb_getAttr(cb,CB_READ_INP )?1:0,
	cb_getAttr(cb,CB_WRITE_INP)?1:0);

	for(c = 0 ; c < cb->numsectors ; c++){
		printf("%2.2i  ",c);
	}printf("\n");
	for(c = 0 ; c < cb->numsectors ; c++){
		if(cb->readPointer == c){
			if(cb_getAttr(cb,CB_READ_INP)){
				printf("^=Ri");
			}else{
				printf("^=Rp");
			}
		}else{
			printf("    ");
		}
	}printf("\n");
	for(c = 0 ; c < cb->numsectors ; c++){
		if(cb->writePointer == c){
			if(cb_getAttr(cb,CB_WRITE_INP)){
				printf("^=Wi");
			}else{
				printf("^=Wp");
			}
		}else{
			printf("    ");
		}
	}printf("\n");
	
}
#endif
