void decode1(int *xp, int *yp, int *zp)
{
	int x, y, z;

	x = *xp;
	y = *yp;
	z = *zp;

	*yp = x;
	*zp = y;
	*xp = z;
}
