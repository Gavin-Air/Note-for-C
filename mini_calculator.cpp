#define  _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
using namespace std;

typedef struct Item {
	short is_d;
	union Data {
		char c;
		int data_i;
		float data_f;
	}data;
}item,*pitem;

bool is_num(char c) 
{
	return (c > 47 && c < 58);
}

int read_raw(item* result, char* raw)
{
	bool start = true;
	item* pi = result;
	char* pr = raw;
	while (*pr) {
		if (is_num(*pr) || *pr == '-' && start || *pr == '.' && is_num(*(pr + 1))) {
			bool is_float = *pr == '.';
			int i = 1;
			for (; is_num(*(pr + i)) || *(pr + i) == '.'; ++i)
				if (*(pr + i) == '.') is_float = true;
			if (is_float) {
				sscanf(pr, "%f", &pi->data.data_f);
				pi->is_d = 2;
			}
			else {
				sscanf(pr, "%d", &pi->data.data_i);
				pi->is_d = 1;
			}
			pr += i;
			++pi;
			start = false;
		}
		else {
			switch (*pr) {
			case ' ':
			case '\n':
			case '\t':
				break;
			case '(':
				pi->data.c = '(';
				start = true;
				pi->is_d = 0;
				++pi;
				break;
			case ')':
				if (start)return pr - raw + 1;
			case '+':
			case '-':
			case '/':
			case '*':
				sscanf(pr, "%c", &pi->data.c);
				start = false;
				pi->is_d = 0;
				++pi;
				break;
			default:
				return pr - raw + 1;
			}
			++pr;
		}
	}
	return 0;
}
class Mystack {
private:
	int length;
	pitem stack[112];
public:
	Mystack(int len) :length(len), stack{ 0 } {}
	void push(pitem a)
	{
		if (length < 112)stack[length++] = a;
	}
	pitem pop()
	{
		if (length)return stack[--length];
	}
	pitem see_top()
	{
		if (length)return stack[length - 1];
	}
	bool is_not_empty()
	{
		return length;
	}
	int len()
	{
		return length;
	}
};
int main()
{
	pitem raw = new item[128]();
	char* raw_c = new char[128]();
	cin.getline(raw_c, 128);
	int err_code = read_raw(raw, raw_c);
	if (err_code) {
		cerr << "Error char in site: " << err_code;
		return err_code;
	}
	pitem myqueue[128] = { 0 };
	//pitem* myqueue = new pitem[128]();
	Mystack* mystack = new Mystack(0);
	int queue_len = 0;
	int i = 0; //queue指针
	while (raw[queue_len].is_d || raw[queue_len].data.c) {
		if (raw[queue_len].is_d) myqueue[i++] = &raw[queue_len];
		else {
			switch (raw[queue_len].data.c) {
			case '+':
			case '-':
				while (mystack->is_not_empty() && mystack->see_top()->data.c != '(') myqueue[i++] = mystack->pop();
				mystack->push(&raw[queue_len]);
				break;
			case '*':
			case '/':
				while (mystack->is_not_empty() && (mystack->see_top()->data.c == '*' || mystack->see_top()->data.c == '/')) myqueue[i++] = mystack->pop();
				mystack->push(&raw[queue_len]);
				break;
			case '(':
				mystack->push(&raw[queue_len]);
				break;
			case ')': //在read_raw中已保证')'不会出现在开头
				while (mystack->see_top()->data.c != '(') {
					myqueue[i++] = mystack->pop();
					if (!mystack->is_not_empty()) {
						cerr << "Unexpected char \')\'";
						return -1;
					}
				}
				mystack->pop();
				break;
			default:
				cerr << "Unexpected error.";
			}
		}
		queue_len++;
	}
	while (mystack->is_not_empty()) myqueue[i++] = mystack->pop();
	//从这里开始，mystack被清空，开始用于存下一个步骤的操作数。
	for (i = 0; myqueue[i]; ++i) {
		if (myqueue[i]->is_d)mystack->push(myqueue[i]);
		else {
			if (mystack->len() < 2) {
				cerr << "Unexpected char: " << myqueue[i]->data.c;
				return -1;
			}
			pitem num1 = mystack->pop();
			pitem num2 = mystack->pop();
			switch (myqueue[i]->data.c) {
			case '+':
				if (num1->is_d == 1 && num2->is_d == 1) num2->data.data_i += num1->data.data_i;
				else {
					num2->data.data_f = (num1->is_d == 1 ? num1->data.data_i : num1->data.data_f) + (num2->is_d == 1 ? num2->data.data_i : num2->data.data_f);
					num2->is_d = 2;
				}
				break;
			case '-':
				if (num1->is_d == 1 && num2->is_d == 1) num2->data.data_i -= num1->data.data_i;
				else {
					num2->data.data_f = (num2->is_d == 1 ? num2->data.data_i : num2->data.data_f) - (num1->is_d == 1 ? num1->data.data_i : num1->data.data_f);
					num2->is_d = 2;
				}
				break;
			case '*':
				if (num1->is_d == 1 && num2->is_d == 1) num2->data.data_i *= num1->data.data_i;
				else {
					num2->data.data_f = (num1->is_d == 1 ? num1->data.data_i : num1->data.data_f) * (num2->is_d == 1 ? num2->data.data_i : num2->data.data_f);
					num2->is_d = 2;
				}
				break;
			case '/':
				num2->data.data_f = (num2->is_d == 1 ? num2->data.data_i : num2->data.data_f) / (num1->is_d == 1 ? num1->data.data_i : num1->data.data_f);
				num2->is_d = 2;
				break;
			}
			mystack->push(num2);
		}
	}
	pitem result = mystack->pop();
	if (mystack->len() > 0) {
		result = mystack->pop();
		cerr << "Unexpected digit: " << (result->is_d == 1 ? result->data.data_i : result->data.data_f);
		return -1;
	}
	cout << "Result: " << (result->is_d == 1 ? result->data.data_i : result->data.data_f) << endl;
	return 0;
}
