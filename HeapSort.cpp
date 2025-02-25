#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}
void item_down(int * a, int dad, int len)
{
	int son = 2 * dad + 1;
	while (son < len) {
		if (son + 1 < len && a[son] < a[son + 1]) ++son;
		if (a[dad] < a[son]) {
			swap(a[dad], a[son]);
			dad = son;
			son = 2 * dad + 1;
		}
		else break;
	}
}
void heap_sort(int* a, int len)
{
	int i = 0;
	for (i = len / 2 - 1; i >= 0; --i) item_down(a, i, len);
	for (i = len - 1; i > 0; --i) {
		swap(a[0], a[i]);
		item_down(a, 0, i);
	}
}

int main()
{
	int num = 30;
	srand(time(nullptr));
	int* A = (int*)calloc(num, sizeof(int));
	for (int i = 0; i < num; ++i) {
		A[i] = rand() % 256;
		printf(" %d", A[i]);
	}
	printf("\n");
	heap_sort(A, num);
	for (int i = 0; i < num; ++i)printf(" %d", A[i]);
	free(A);
	return 0;
}