#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef int Elemtype;
typedef struct TNode {
	Elemtype data;
	struct TNode* L;
	struct TNode* R;
}Node, * pNode;
class BiTree {
private:
	pNode root;
	void free_tree(pNode r)
	{
		if (r->L)free_tree(r->L);
		if (r->R)free_tree(r->R);
		free(r);
	}
	bool tree_insert(pNode& r, Elemtype a)
	{
		if (r) {
			if (a == r->data)return false;
			else if (a > r->data) tree_insert(r->R, a);
			else tree_insert(r->L, a);
		}
		else {
			r = (pNode)calloc(1, sizeof(Node));
			if (r) {
				r->data = a;
				return true;
			}
			else return false;
		}
	}
	void tree_list(pNode r)
	{
		if (r) {
			tree_list(r->L);
			printf(" %d ", r->data);
			tree_list(r->R);
		}
	}
	Elemtype find_max(pNode& r)
	{
		if (r->R)find_max(r->R);
		else {
			pNode temp = r;
			Elemtype m = 0;
			r = r->L;
			m = temp->data;
			free(temp);
			return m;
		}
	}
	bool tree_pop(pNode& r, Elemtype a)
	{
		if (r->data == a) {
			pNode temp = r;
			if (!r->L) {
				r = r->R;
				free(temp);
			}
			else if (!r->R) {
				r = r->L;
				free(temp);
			}
			else {
				if (!r->L->R) {
					r = r->L;
					r->R = temp->R;
					free(temp);
				}
				else r->data = find_max(r->L->R);
			}
			return true;
		}
		else if (a > r->data) {
			if (r->R)return tree_pop(r->R, a);
			else return false;
		}
		else {
			if (r->L)return tree_pop(r->L, a);
			else return false;
		}
	}
public:
	BiTree()
	{
		root = nullptr;
	}
	~BiTree()
	{
		free_tree(root);
	}
	bool insert(Elemtype in)
	{
		return tree_insert(root, in);
	}
	void list()
	{
		tree_list(root);
	}
	bool pop(Elemtype in)
	{
		return tree_pop(root, in);
	}
};

int main()
{
	BiTree a;
	int in = 0;
	char ch = '\0';
	printf("Hi, there.\n1:Insert, 2:Delete, 3:List.\n");
	while (1) {
		ch = _getch();
		switch (ch) {
		case'1': {
			system("cls");
			printf("Insert.  Click '0' to back.\nThe number you will insert:");
			scanf("%d", &in);
			if (a.insert(in))printf("Inserting Successful.\n");
			else printf("Inserting Fail.\n");
		}break;
		case'2': {
			system("cls");
			printf("Delete.  Click '0' to back.\nThe number you will delete:");
			scanf("%d", &in);
			if (a.pop(in))printf("Deleting Successful.\n");
			else printf("Data not find.\n");
		}break;
		case'3': {
			system("cls");
			printf("View all.  Click '0' to back.\n");
			a.list();
		}break;
		case '0': {
			system("cls");
			printf("Hi, there.\n1:Insert, 2:Delete, 3:List.\n");
		}break;
		case '9': return 0;
		default:continue;
		}
		fflush(stdin);
	}
}
