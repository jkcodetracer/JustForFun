
enum cb_status{
	CB_BUF_WRITE_INP,
	CB_BUF_WRITEONLY,
	CB_BUF_READ_INP,
	CB_BUF_READONLY,
};

typedef struct _cb_buf_t{
	char* mem;
	int read_index;
	int write_index;
	int status;
	int num_sectors;
	int sectors_size;
}cb_buf_t;

char*
cb_read(cb_buf_t *cb)
{
	if((cb->read_index == cb->write_index) &&
		!cb_get_attr(cb, CB_BUF_READONLY))
	{
		return;
	}

	if(cb_get_attr(cb, CB_BUF_READ_INP))
	{
		return ;
	}

	cb_set_attr(cb, CB_BUF_READ_INP, 1);
	return cb_sector_to_ptr(cb, cb->read_index);
}

void 
cb_done_read(cb_buf_t *cb)
{
	if(!cb_get_attr(cb, CB_BUF_READ_INP))
	{
		return;
	}

	if(cb_get_attr(cb, CB_BUF_READONLY))
	{
		cb_set_attr(cb, CB_BUF_READONLY, 0);
	}

	if(cb->read_index + 1 == cb->num_sectors)
	{
		cb->read_index = 0;
	} else {
		cb->read_index++;
	}

	if(cb->read_index == cb->write_index)
	{
		cb_set_attr(cb, CB_BUF_WRITEONLY, 1);
	}

	cb_set_attr(cb, CB_BUF_READ_INP, 0);
}
