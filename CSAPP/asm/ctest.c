char ctest(int a, int b, int c)
{
	char t1 = a < b;
	char t2 = b < (unsigned int)a;
	char t3 = (long long)c >= (long long) a;
	char t4 = (unsigned int) a != (unsigned int) c;
	char t5 = c > b;
	char t6 = a > 0;

	return t1 + t2 + t3 +t4 + t5 + t6;
}
