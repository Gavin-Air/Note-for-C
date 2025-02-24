#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef int Elemtype;
typedef struct Node{
	Elemtype data;
	struct Node* next;
}LNode,*pLNode;
class LinkList {
private:
	int length;
	pLNode head;
public:
	LinkList()
	{
		length = 0;
		head = (pLNode)calloc(1,sizeof(LNode));
		if (head) printf("List %d Ready.\n", head->data);
		else printf("Error!\n");
	}
	LinkList(Elemtype head_data)
	{  //可以自定义头节点数据的构造函数；别问，问就是好玩。
		length = 0;
		head = (pLNode)malloc(sizeof(LNode));
		if (head) {
			head->data = head_data;
			head->next = nullptr;
			printf("List %d Ready.\n", head->data);
		}
		else printf("Error!\n");
	}
	~LinkList()
	{
		pLNode will_free;
		while (head->next) {
			will_free = head;
			head = head->next;
			free(will_free);
		}
		free(head);
	}
	void test()
	{  //测试用函数
		if (head->next) printf("true0\n");
		if (head->next == NULL)printf("true1\n");
		if (head->next == nullptr) printf("true2\n");
	}
	bool insert_from_head(Elemtype in)
	{  //下面这段代码用c++新写法只要一行：head->next = new LNode{ in, head->next };
		pLNode temp = (pLNode)malloc(sizeof(LNode));
		if (temp) {
			temp->data = in;
			temp->next = head->next;
			head->next = temp;
			++length;
			return true;
		}
		else return false;
	}
	bool insert_from_end(Elemtype in)
	{
		pLNode temp = head;
		if (temp) {
			while (temp->next) temp = temp->next;
			temp->next = (pLNode)calloc(1, sizeof(LNode));
			temp->next->data = in;
			++length;
			return true;
		}
		else return false;
	}
	Elemtype find_by_position(int pos)
	{
		pLNode temp = head;
		if (pos<1 && pos>length) {
			printf("Out of List!!!\n");
			return -4294967296;  //-2^32
		}
		for (int i = 0; i < pos; ++i) temp = temp->next;
		return temp->data;
	}
	int find_by_data(Elemtype da)
	{
		pLNode temp = head->next;
		int i = 1;
		while (temp && da != temp->data) {
			temp = temp->next;
			++i;
		}
		if (temp)return i;
		else return 0;
	}
	bool insert_by_position(int pos, Elemtype in)
	{
		pLNode temp0 = (pLNode)malloc(sizeof(LNode));
		pLNode temp1 = head;
		if (pos<1 || pos>length) {
			printf("Out of List!!!\n");
			return false;
		}
		if (temp0) {
			for (int i = 0; i < pos - 1; ++i) temp1 = temp1->next;
			temp0->data = in;
			temp0->next = temp1->next;
			temp1->next = temp0;
			++length;
			return true;
		}
		else return false;
	}
	bool delete_by_position(int pos)
	{
		if (pos<1 || pos>length) {
			printf("Out of List!!!\n");
			return false;
		}
		pLNode temp0 = head;
		for (int i = 0; i < pos - 1; ++i) temp0 = temp0->next;
		pLNode temp1 = temp0->next;
		temp0->next = temp1->next;
		free(temp1);
		--length;
		return true;
	}
	void list_all()
	{
		pLNode temp = head;
		printf("List %d:", temp->data);
		for (int i = 0; i < length; ++i) {
			temp = temp->next;
			printf(" %d", temp->data);
		}
		printf("\n^_^");
	}
};

int main()
{
	LinkList a(114514);
	int pos = 0, in = 0;
	char ch = '\0';
	printf("Hi, there.\n1:Insert to head, 2:Insert to end, 3:Find by position, 4:Find by data, 5:Insert by position, 6:Delete by position, 9:View all.\n");
	while (1) {
		ch = _getch();
		switch (ch) {
		case '1': {
			system("cls");
			printf("Insert to head.  Click '0' to back.\nThe number you will insert:");
			scanf("%d", &in);
			if (a.insert_from_head(in))printf("Inserting Successful.\n");
			else printf("Inserting Fail.\n");
		}break;
		case '2': {
			system("cls");
			printf("Insert to end.  Click '0' to back.\nThe number you will insert:");
			scanf("%d", &in);
			if (a.insert_from_end(in))printf("Inserting Successful.\n");
			else printf("Inserting Fail.\n");
		}break;
		case '3': {
			system("cls");
			printf("Find by position.  Click '0' to back.\nThe position you will find:");
			scanf("%d", &pos);
			printf("Data in List[%d]: %d\n", pos, a.find_by_position(pos));
		}break;
		case '4': {
			system("cls");
			printf("Find by data.  Click '0' to back.\nThe data you will find:");
			scanf("%d", &in);
			int p = a.find_by_data(in);
			if (p)printf("Data %d is in List[%d].\n", in, p);
			else printf("Data is not found.\n");
		}break;
		case '5': {
			system("cls");
			printf("Insert by position.  Click '0' to back.\nThe position you will insert:");
			scanf("%d", &pos);
			printf("The number you will insert:");
			scanf("%d", &in);
			if (a.insert_by_position(pos, in))printf("Inserting Successful.\n");
			else printf("Inserting Fail.\n");
		}break;
		case'6': {
			system("cls");
			printf("Delete by position.  Click '0' to back.\nThe position you will delete:");
			scanf("%d", &pos);
			if (a.delete_by_position(pos))printf("Deleting Successful.\n");
			else printf("Deleting Fail.\n");
		}break;
		case'9': {
			system("cls");
			printf("View all.  Click '0' to back.\n");
			a.list_all();
		}break;
		case '0': {
			system("cls");
			printf("1:Insert to head, 2:Insert to end, 3:Find by position, 4:Find by data, 5:Insert by position, 6:Delete by position, 9:View all.\n");
		}break;
		case 'q': {
			//a.~LinkList();  !!!注意，析构函数在程序接受时总会自动调用，如果手动调用就会被多次调用。
			return 0;
		}
		default: continue;
		}
		fflush(stdin);
	}
}