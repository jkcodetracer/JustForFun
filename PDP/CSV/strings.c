
void strings(char *name, FILE *fin)
{
	if (fin == NULL)
	{
		return;
	}
	int c;
	char buf[BUFFERSIZE] = {0};

	do {
		for(int i = 0;((c = getc(fin)) != EOF);i++ )	
		{
			if (!isprint(c) || i > BUFFERSIZE)
			{
				break;	
			}
			name[i] = c;
		}
		if (i >= MINSIZE)
		//使用这种方式控制buf的长度，因为没有为buf留结束符号。
			printf("%s: %.*s\n",name, i, buf);
	}while(c != EOF);
}
