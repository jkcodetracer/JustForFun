int test(int y, int x)
{
	switch(x)
	{
		case 100:
		y = 10;
		break;
		case 101:
		y = 100;
		break;
		case 102:
		y = 124;
		break;
		case 103:
		y = 12455;
		break;
		case 133:
		y = 12;
		break;
		default:
		y = 0;
	}

	return y;
}
