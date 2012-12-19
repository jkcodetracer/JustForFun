int loop(int x, int y, int n) 
{
	int result = 0;
	int i;
	for (i = n-1;  i >= 0; )
	{
		result +=  x * y;
		i = i -x;
	}
	return result;
}
