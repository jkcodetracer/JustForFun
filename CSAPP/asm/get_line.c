

void read_line()
{
	char buff[1024] = {0};
	int len = 0;

	while(1)
	{
		fgets(buff, 1024, stdin);
		
		len = strlen(buff);
		if(buff[len-1] =='\n' || buff[len - 2] == EOF)
		{
			break;
		}
		printf("%s", buff);
	}

}

void good_echo()
{
	char buf[BUFSIZE];
	int i;

	while(1)
	{
		if (!fgets(buf, BUFSIZE, stdin))
			return;
		for (i = 0; buf[i] && buf[i] != '\n'; i++)
		{
			if (putchar(buf[i]) == EOF)
				return;
		}
		if (buf[i] == '\n')
		{
			putchar('\n');
			return;
		}
	}
}
