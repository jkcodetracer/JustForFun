#define N 16
typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val)
{
	int i = N;
	int *B = &A[0][0];
	
	do{
		*B = val;
		B += N+1;
		i--;
	}while(i>=0);
}
