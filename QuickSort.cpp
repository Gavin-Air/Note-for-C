#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* turn(int* i, int* j)
{
	int flag = *i;
	while (i < j) {
		while (i < j && *j >= flag)--j;
		*i = *j;
		while (i < j && *i <= flag)++i;
		*j = *i;
	}
	*i = flag;
	return i;
}
void quick_sort(int* i, int* j)
{
	if (i < j) {
		int* pos = turn(i, j);
		quick_sort(i, pos - 1);
		quick_sort(pos + 1, j);
	}
}

int main()
{
	int num = 16;
	srand(time(nullptr));
	int* A = (int*)calloc(num, sizeof(int));
	for (int i = 0; i < num; ++i) {
		A[i] = rand() % 16;
		printf(" %d", A[i]);
	}
	printf("\n");
	quick_sort(A, A + num - 1);
	for (int i = 0; i < num; ++i)printf(" %d", A[i]);
	free(A);
	return 0;
}