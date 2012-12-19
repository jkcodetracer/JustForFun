int loop_while(int a, int b)
{
	int i = 0; 
	int result = a;
	
	if (i >= 256)
	    goto done;
	loop:
		result += a;
		a -= b;
		i += b;
	if (i < 256) 
	{
		goto loop;
	}

done:
	return result;
}
