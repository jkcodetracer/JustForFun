/*
 * @FileName: easy_malloc.c
 * @Author: wzj
 * @Brief: 
 * 1.经典的隐式链表。 
 * 2.双字对齐的思想。 
 * 3.init之后，总大小不再改变。 
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年05月20日星期日00:04:43
 * 
 */ 

static char *mem_start_brk;	//first byte
static char *mem_brk;		//last byte
static char *mem_max_addr; 	//max address of heap

void
mem_init(int size)
{
	mem_start_brk = (char*)Malloc(size);
	mem_brk = mem_start_brk;
	mem_max_addr = mem_start_brk + size;
}

void*
mem_sbrk(int incr)
{
	char *old_brk = mem_brk;

	if((incr < 0)|| ((mem_brk + incr) > mem_max_addr))
	{
		errno = ENOMEM;
		return (void*) -1;
	}

	mem_brk += incr;
	return old_brk;
}


//basic macro
#define WSIZE	(4) 	//word size
#define DSIZE	(8)		//double word
#define CHUNKSIZE	(1 << 12)	//initial heap size
#define OVERHEAD	(8)

#define MAX(x, y)	((x) > (y)? (x):(y))
#define PACK(size, alloc)	((size) | (alloc))
#define GET(p)		(*(size_t *)(p))
#define PUT(p, val) (*(size_t *)(p) = (val))
//最重要的一点，DWORD对齐！减少碎片？
//始终DWORD对齐。
//使用DWORD做单位是很巧妙的，这样最小的3bit可以用作标记，省了空间。
#define GET_SIZE(p) 	(GET(p) & ~0x7) //byte...
#define GET_ALLOC(p)	(GET(p) & 0x1) 	//mark alloced
//head && foot
#define HDRP(bp) 		((char*)(bp) - WSIZE)
//为什么减去DSIZE呢？正好减去头和尾的长度。
#define FTRP(bp) 		((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
//最小块就是8个字节了。

#define NEXT_BLKP(bp)	((char*)(bp) + GET_SIZE(((char*)(bp) - WSIZE)))
#define PREV_BLKP(bp) 	((char*)(bp) - GET_SIZE(((char*)(bp) - DSIZE)))

int
mm_init(void)
{
	if ((heap_listp = mem_sbrk(4*WSIZE)) == NULL)
		return -1;
	//初始化一个空闲块，作为dummy节点。
	PUT(heap_listp, 0);
	PUT(heap_listp + WSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp + DSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp + WSIZE + DSIZE, PACK(0, 1));
	
	heap_listp += DSIZE;
	//扩展字节，用于初始化可分配的空间	
	if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;
	return 0;
}

static void*
extend_heap(size_t words)
{
	char *bp;
	size_t size;
	//maintain alignment	
	size = (words % 2)?(words + 1) * WSIZE : words * WSIZE;
	if((int)(bp = mem_sbrk(size)) < 0)
	{
		return NULL;
	}
	//做未分配标记
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

	return coalesce(bp);
}

void
mm_free(void *bp)
{
	size_t size = GET_SIZE(HDRP(bp));

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	//合并
	coalesce(bp);
}

static void*
coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

	if (prev_alloc && next_alloc)
	{
		return bp;
	} else if (prev_alloc && !next_alloc) {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
		return bp;
	} else if (!prev_alloc && next_alloc) {
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		return (PREV_BLKP(bp));
	} else {
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
			GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(HDRP(NEXT_BLKP(bp)), PACK(size, 0));
		return PREV_BLKP(bp);
	}
}

void*
find_fit(size_t asize)
{
	char *bp = NULL;
	char *tmp_heap = heap_listp;

	if(asize <= 0)	
	{
		return NULL;
	}
	
	while(1)
	{
		if((GET_SIZE(HDRP(NEXT_BLKP(tmp_heap))) == 0) && 
			(GET_ALLOC(HDRP(NEXT_BLKP(tmp_heap))) == 1))
		{
			break;
		}
		
		if((GET_ALLOC(HDRP(tmp_heap)) == 0) ||
			(GET_SIZE(HDRP(tmp_heap)) > asize))
		{
			bp = tmp_heap;		
		}

		tmp_heap = NEXT_BLKP(tmp_heap);
	}

	return bp;
}

static void
place(void *bp, size_t asize)
{
	int old_size = 0;

	old_size = GET_SIZE(HDRP(bp));

	PUT(HDRP(NEXT_BLKP(bp)), PACK(old_size-asize, 0));
	PUT(FTRP(NEXT_BLKP(bp)), PACK(old_size-asize, 0));
	if(old_size - asize < OVERHEAD)
	{
		coalesce(NEXT_BLKP(bp));	
	}

	PUT(HDRP(bp), PACK(asize, 1));	
}

void*
mm_malloc(size_t size)
{
	size_t asize;
	size_t extendsize;
	char *bp;

	if(size <= 0)
		return NULL;
	//align	
	if(size <= DSIZE)
		asize = DSIZE + OVERHEAD;
	else
		asize = DSIZE * ((size + (OVERHEAD) + (DSIZE-1)) / DSIZE);
	
	//search
	if ((bp = find_fit(asize)) != NULL)
	{
		//alloc
		place(bp, asize);
		return bp;
	}

	extendsize = MAX(asize, CHUNKSIZE);
	if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
		return NULL;
	//alloc
	place(bp, asize);
	return bp;
}
