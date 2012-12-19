/*
 * @FileName: state_cirbuf.c
 * @Author: wzj
 * @Brief: 
 * 1.state circle buf 
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年07月29日星期日21:06:23
 * 
 */ 
#include <stdio.h>
/**
 * \breif cb status
 */
enum cb_status{
	CB_BUF_WRITEONLY = 0,	
	CB_BUF_WRITE_INP,
	CB_BUF_READONLY,
	CB_BUF_READ_INP,
};

typedef struct _cb_buf_t{
//	int size;			/**< buffer size */
	char* buf;			/**< cb buffer */
	int status;			/**< buffer status, we should process it by bit calc */
	int read_index;		/**< read pointer */
	int write_index;	/**< write pointer */
	int num_sectors; 	/**< all sectors */
	int sector_size;	/**< the size of each sector */
}cb_buf_t;

//set the buffer state
void 
cb_set_attr(cb_buf_t *cb, int attribute, int val)
{
	if(val)	
	{ //set value
		cb->status |= (1 << attribute);
	} else {
	  //clean value
		cb->status &= ~(1 << attribute);
	}
}
//judge the state is ok or not
int cb_get_attr(cb_buf_t *cb, int attribute)
{
	return (cb->status & (1 << attribute));
}
//seperat one block out
char* cb_sector_to_ptr(cb_buf_t *cb, int sector)
{
	return (cb->buf + (sector * (cb->sector_size)));
}
//init the buffer
void
cb_init(cb_buf_t *cb, char* mem, int num_sectors, int sector_size)
{
	cb->buf = mem;
	cb->num_sectors = num_sectors;
	cb->sector_size = sector_size;
	cb->write_index = 0;
	cb->read_index = 0;
	cb->status = 0;
	cb_set_attr(cb, CB_BUF_WRITEONLY, 1);
}
//get the read pointer
char*
cb_read(cb_buf_t *cb)
{
	if((cb->read_index == cb->write_index) &&
		!cb_get_attr(cb, CB_BUF_READONLY))
	{
		return NULL;
	}
	
	if(cb_get_attr(cb, CB_BUF_READ_INP))
	{
		return NULL;
	}
	
	cb_set_attr(cb, CB_BUF_READ_INP, 1);
	return (cb_sector_to_ptr(cb, cb->read_index));
}
//finish read
void 
cb_done_read(cb_buf_t *cb)
{
	if(!cb_get_attr(cb, CB_BUF_READ_INP))
	{
		return ;
	}

	if(cb_get_attr(cb, CB_BUF_READONLY))
	{
		cb_set_attr(cb, CB_BUF_READONLY, 0);
	}

	if(cb->read_index + 1 == cb->num_sectors)
	{
		cb->read_index = 0;
	} else {
		cb->read_index ++;
	}

	if(cb->read_index == cb->write_index) 
	{
		cb_set_attr(cb, CB_BUF_WRITEONLY, 1); 
	}

	cb_set_attr(cb, CB_BUF_READ_INP, 0);
}
//cancel read
void
cb_cancel_read(cb_buf_t *cb)
{
	if(!cb_get_attr(cb, CB_BUF_READ_INP))
	{
		return;
	}
	
	cb_set_attr(cb, CB_BUF_READ_INP, 0);
}

char*
cb_write(cb_buf_t *cb)
{
	if((cb->read_index == cb->write_index) &&
		!cb_get_attr(cb, CB_BUF_WRITEONLY))	
	{
		return NULL;
	}
	if(cb_get_attr(cb, CB_BUF_WRITE_INP))
	{
		return NULL;
	}

	cb_set_attr(cb, CB_BUF_WRITE_INP, 1);
	return cb_sector_to_ptr(cb, cb->write_index);
}

void
cb_done_write(cb_buf_t *cb)
{
	if(!cb_get_attr(cb, CB_BUF_WRITE_INP))
	{
		return ;
	}

	if(cb_get_attr(cb, CB_BUF_WRITEONLY))
	{
		cb_set_attr(cb, CB_BUF_WRITEONLY, 0);
	}

	if(cb->write_index+1 == cb->num_sectors)
	{
		cb->write_index = 0;
	} else {
		cb->write_index ++;
	}
	
	if(cb->write_index == cb->read_index)
	{
		cb_set_attr(cb, CB_BUF_READONLY, 1);
	}
	cb_set_attr(cb, CB_BUF_WRITE_INP, 0);
}

void
cb_cancel_write(cb_buf_t *cb)
{
	if(!cb_get_attr(cb, CB_BUF_WRITE_INP))
	{
		return;
	}

	cb_set_attr(cb, CB_BUF_WRITE_INP, 0);
}


#ifdef CTDEBUG
#include "../Jlog.h"
#include <stdlib.h>
#define BUF_LEN	(1024)

int
main()
{
	cb_buf_t cb;
	char *mem = (char*)malloc(BUF_LEN);
	if(mem == NULL)
	{
		WRITELOG("malloc failed! return...");
		return -1;
	}

	cb_init(&cb, mem, BUF_LEN/sizeof(int), sizeof(int));
	
	int i = 0;
	char *tmpbuf = NULL;
	for(i = 0; i < BUF_LEN/sizeof(int); i++)
	{
		tmpbuf = cb_write(&cb);			
		if(tmpbuf == NULL)	
		{
			WRITELOG("get from cb failed %d", i);	
		} else {
			WRITELOG("get success: %p\n", tmpbuf);
		}

		memcpy(tmpbuf, &i, sizeof(int));

		cb_done_write(&cb);
	}

	for(i = 0; i < BUF_LEN/sizeof(int); i++)
	{
		tmpbuf = cb_read(&cb);
		if(tmpbuf == NULL)
		{
			WRITELOG("read from ccb failed %d", i);
		} else {
			WRITELOG("read success: %d", (int)(*tmpbuf));
		}

		cb_done_read(&cb);
	}

	return 0;
}

#endif
