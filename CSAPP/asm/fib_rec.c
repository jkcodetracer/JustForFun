int fib_rec(int n)
{
	int prev_val, val;
	if (n <= 2)
		return 1;
	prev_val = fib_rec(n-2);
	val = fib_rec(n-1);
	return prev_val + val;
}
