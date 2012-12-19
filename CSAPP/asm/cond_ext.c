void cond(int a, int *p)
{
	if (p == 0)
		goto EXIT;
	if (a > 0)
		*p +=a;
EXIT:
	return;
}

