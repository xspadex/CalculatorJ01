// CalculatorJ.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

extern short PriorTab[7][7] = { {1,1,0,0,0,1,1},{1,1,0,0,0,1,1},{1,1,1,1,0,1,1},{1,1,1,1,0,1,1},{0,0,0,0,0,2,-1},{1,1,1,1,-1,1,1},{0,0,0,0,0,-1,2} };

SNode* InitSNode(SNode *p) {
	p = (SNode*)malloc(sizeof(SNode));
	p->next = NULL;
	return p;
}

SNode* push(SNode *head, double i) {
	SNode *newNode= (SNode*)malloc(sizeof(SNode));
	newNode->next = head;
	newNode->data = i;
	return newNode;
}

double top(SNode *head) {
	return head->data;
}

bool EmptyStack(SNode *head) {
	if (head->next == NULL) return true;
	else return false;
}

SNode* pop(SNode *head) {
	SNode *tmp = head->next;
	free(head);
	return tmp;
}






Status InitList_Sq(SqList &L) {
	L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status Zero_Sq(SqList &L) {
	for (int i = 0; i < L.listsize; i++) {
		L.elem[i] = 0;
	}
	L.length = L.listsize;
	return OK;
}

Status Display_Sq(SqList &L) {
	for (int i = 0; i < L.length; i++) {
		cout << L.elem[i] << " ";
	}
	cout << endl;
	return OK;
}

Status Display_Pl(SqList &L) {
	if (L.length == 0) return OK;
	cout << L.elem[0] << " ";
	for (int i = 1; i < L.length; i++) {
		cout << L.elem[i] << "x^"<<i<<" ";
	}
	cout << endl;
	return OK;
}

Status ExpandList_Sq(SqList &L) {
	int *newbase;
	newbase = (int *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(int));
	if (!newbase) exit(OVERFLOW);
	L.elem = newbase;
	L.listsize += LISTINCREMENT;
	return OK;
}

Status DestroyList_Sq(SqList &L) {
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}

Status Get(SqList L, int i, int &e) {
	if (i <= 0 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}

Status Put(SqList &L, int i, int e) {
	//加在i后面,i可取0
	if (i < 0 || i > L.length) return ERROR;
	if (L.length + 1 > L.listsize) ExpandList_Sq(L);
	if (L.length == 0) {
		L.elem[0] = e;
		L.length++;
		return OK;
	}
	int p = L.length;
	while (p > i){
		L.elem[p] = L.elem[p - 1];
		p--;
	}
	L.elem[i] = e;
	L.length++;
	return OK;
}

Status Clear(SqList &L) {
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = 0;
	}
	L.length = 0;
	return OK;
}

Status Plus_vector(SqList &L1, SqList &L2, SqList &out) {
	if (L1.length != L2.length) exit(ERROR);
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < L1.length) ExpandList_Sq(out);
	for (int i = 0; i < L1.length; i++) {
		out.elem[i] = L1.elem[i] + L2.elem[i];
	}
	out.length = L1.length;
	return OK;
}

Status Minus_vector(SqList &L1, SqList &L2, SqList &out) {
	if (L1.length != L2.length) exit(ERROR);
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < L1.length) ExpandList_Sq(out);
	for (int i = 0; i < L1.length; i++) {
		out.elem[i] = L1.elem[i] - L2.elem[i];
	}
	out.length = L1.length;
	return OK;

}

Status Plus_poly(SqList &L1, SqList &L2, SqList &out) {
	int maxlength = (L1.length > L2.length) ? L1.length : L2.length;
	int minlength = (L1.length < L2.length) ? L1.length : L2.length;
	int maxid = (L1.length > L2.length) ? 1 : 2;
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < maxlength) ExpandList_Sq(out);
	for (int i = 0; i < minlength; i++) {
		out.elem[i] = L1.elem[i] + L2.elem[i];
	}
	for (int i = minlength; i < maxlength; i++) {
		if (maxid == 1) out.elem[i] = L1.elem[i];
		else out.elem[i] = L2.elem[i];
	}
	out.length = maxlength;
	return OK;
}

Status Minus_poly(SqList &L1, SqList &L2, SqList &out) {
	int maxlength = (L1.length > L2.length) ? L1.length : L2.length;
	int minlength = (L1.length < L2.length) ? L1.length : L2.length;
	int maxid = (L1.length > L2.length) ? 1 : 2;
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < maxlength) ExpandList_Sq(out);
	for (int i = 0; i < minlength; i++) {
		out.elem[i] = L1.elem[i] - L2.elem[i];
	}
	for (int i = minlength; i < maxlength; i++) {
		if (maxid == 1) out.elem[i] = L1.elem[i];
		else out.elem[i] = -L2.elem[i];
	}
	out.length = maxlength;
	return OK;

}

Status Times_Dot_vector(SqList &L1, SqList &L2, double &out) {
	out = 0;
	if (L1.length != L2.length) exit(ERROR);
	for (int i = 0; i < L1.length; i++) {
		out += L1.elem[i] * L2.elem[i];
	}
	return OK;
}

Status Absolute_vector(SqList &L,double &out) {
	out = 0;
	for (int i = 0; i < L.length; i++) {
		out += L.elem[i] * L.elem[i];
	}
	out = sqrt(out);
	return OK;
}

Status Cos_vector(SqList &L1, SqList &L2, double &out) {
	if (L1.length != L2.length) exit(ERROR);
	double abs1, abs2,timesR;
	Times_Dot_vector(L1, L2, timesR);
	Absolute_vector(L1, abs1);
	Absolute_vector(L2, abs2);
	out = timesR / (abs1*abs2);
	return OK;
}

Status Times_poly(SqList &L1, SqList &L2, SqList &out) {
	int maxlength = (L1.length > L2.length) ? L1.length : L2.length;
	int minlength = (L1.length < L2.length) ? L1.length : L2.length;
	int maxid = (L1.length > L2.length) ? 1 : 2;
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < maxlength + minlength) ExpandList_Sq(out);
	Zero_Sq(out);
	for (int i = 0; i < maxlength; i++) {
		for (int j = 0; j < minlength; j++) {
			if (maxid == 1) {
				out.elem[i + j] += L1.elem[i] * L2.elem[j];
			}
			else {
				out.elem[i + j] += L1.elem[j] * L2.elem[i];
			}
		}
	}
	out.length = maxlength + minlength - 1;
	return OK;
}

Status Derivate_poly(SqList &L, SqList &out) {
	if (out.elem == NULL)  InitList_Sq(out);
	while (out.listsize < L.length) ExpandList_Sq(out);
	for (int i = 0; i < L.length-1; i++) {
		out.elem[i] = L.elem[i + 1] * (i + 1);
	}
	out.length = L.length - 1;
	return OK;
}

short getPrior(char left, char right) {
	int leftn, rightn;
	switch (left)
	{
	case '+':
		leftn = 0;
		break;
	case '-':
		leftn = 1;
		break;
	case '*':
		leftn = 2;
		break;
	case '/':
		leftn = 3;
		break;
	case '(':
		leftn = 4;
		break;
	case ')':
		leftn = 5;
		break;
	case '#':
		leftn = 6;
		break;
	default:
		leftn = 6;
		break;
	}

	switch (right)
	{
	case '+':
		rightn = 0;
		break;
	case '-':
		rightn = 1;
		break;
	case '*':
		rightn = 2;
		break;
	case '/':
		rightn = 3;
		break;
	case '(':
		rightn = 4;
		break;
	case ')':
		rightn = 5;
		break;
	case '#':
		rightn = 6;
		break;
	default:
		rightn = 6;
		break;
	}

	return PriorTab[leftn][rightn];
}

short getNFromC(char opt) {
	short leftn;
	switch (opt)
	{
	case '+':
		leftn = 0;
		break;
	case '-':
		leftn = 1;
		break;
	case '*':
		leftn = 2;
		break;
	case '/':
		leftn = 3;
		break;
	case '(':
		leftn = 4;
		break;
	case ')':
		leftn = 5;
		break;
	case '#':
		leftn = 6;
		break;
	default:
		leftn = 6;
		break;
	}
	return leftn;
}

char getCFromN(short opt) {
	char leftn;
	switch (opt)
	{
	case 0:
		leftn = '+';
		break;
	case 1:
		leftn = '-';
		break;
	case 2:
		leftn = '*';
		break;
	case 3:
		leftn = '/';
		break;
	case 4:
		leftn = '(';
		break;
	case 5:
		leftn = ')';
		break;
	case 6:
		leftn = '#';
		break;
	default:
		leftn = '#';
		break;
	}
	return leftn;
}

double operate(double left, double right, char opt) {
	switch (opt)
	{
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	case '*':
		return left * right;
		break;
	case '/':
		return left / right;
		break;
	default:
		break;
	}
	return -1;
}

bool isNum(char c) {
	if ((c >= 48) && (c <= 57)) return true;
	else return false;
}

Status CalExpression() {
	SNode *num = (SNode*)malloc(sizeof(SNode));
	num->next = NULL;
	SNode *opt = (SNode*)malloc(sizeof(SNode));
	opt->next = NULL;
	SNode *buff = (SNode*)malloc(sizeof(SNode));
	buff->next = NULL;
	opt = push(opt, 7);
	char c;
	int n = 0;
	c = getchar();
	while (c != '#') {
		if (isNum(c)) {
			buff = push(buff, c - '0');
		}
		else {
			if (!EmptyStack(buff)) {
				int count = 0;
				n = 0;
				while (!EmptyStack(buff)) {
					n += top(buff)*pow(10, count);
					buff = pop(buff);
					count++;
				}
				num = push(num, n);
			}
			//如果左小于右
			if (getPrior(getCFromN(top(opt)), c) == 0) {
				opt = push(opt, getNFromC(c));
			}
			//如果左大于右
			else if (getPrior(getCFromN(top(opt)), c) == 1) {
				while (getPrior(getCFromN(top(opt)), c) == 1) {
					double right = top(num);
					num = pop(num);
					double left = top(num);
					num = pop(num);
					num = push(num, operate(left, right, getCFromN(top(opt))));
					opt = pop(opt);
				}
				if (getPrior(getCFromN(top(opt)), c) == 2) {
					opt = pop(opt);
				}
				else opt = push(opt, getNFromC(c));
			}
			//如果相等（等号）
			else if (getPrior(getCFromN(top(opt)), c) == 2) {
				opt = pop(opt);
			}
		}
		c = getchar();
	}

	if (!EmptyStack(buff)) {
		int count = 0;
		n = 0;
		while (!EmptyStack(buff)) {
			n += top(buff)*pow(10, count);
			buff = pop(buff);
			count++;
		}
		num = push(num, n);
	}
	
	while (getPrior(getCFromN(top(opt)), c) == 1) {
		double right = top(num);
		num = pop(num);
		double left = top(num);
		num = pop(num);
		num = push(num, operate(left, right, getCFromN(top(opt))));
		opt = pop(opt);
	}

	cout << top(num) << endl;
	num = pop(num);
	free(num);
	free(opt);
	free(buff);
	return OK;
}

int min()
{
	//orders:create,display,clear,destroy,plusv,plusp,minusv,minusp,cosv,timesp,derivate
	int order = 0;
	int tmp = 0;
	int length = 0;
	int length21 = 0;
	int length22 = 0;
	cout << "please order: 1=create 2=plus 3=minus 4=cosv 5=timesp 6=derivate" << endl;
	while (true) {
		cin >> order;
		if (order == 1/*create*/ || order == 2/*plus*/ || order == 3/*minus*/ || order == 4/*cosv*/ || order == 5/*timesp*/ || order == 6/*derivate*/) break;
		else cout << "wrong order" << endl;
	}
	switch (order)
	{
	case 1:
		cout << "Create Mode On, please enter your SqList." << endl;
		SqList L;
		InitList_Sq(L);
		cout << "Enter the length." << endl;
		cin >> length;
		cout << "Enter the "<< length << " elements." << endl;
		for (int i = 0; i < length;i++) {
			cin >> tmp;
			Put(L, L.length, tmp);
		}
		while (true) {
			cout << "Please order: 1=display 2=clear 3=destroy 4=exit" << endl;
			cin >> order;
			if (order == 1/*display*/ || order == 2/*clear*/ || order == 3/*destroy*/ || order == 4/*exit*/) {
				switch (order)
				{
				case 1:
					Display_Sq(L);
					break;
				case 2:
					Clear(L);
					Display_Sq(L);
					break;
				case 3:
					DestroyList_Sq(L);
					cout << "List destroyed, please exit create mode." << endl;
					break;
				case 4:
					break;
				default:
					break;
				}
				if (order == 4) break;
			}
			else cout << "wrong order" << endl;
		}
		DestroyList_Sq(L);
		break;
	case 2:
		cout << "Plus Mode On, please enter your type. 1=vector,2=polynomial" << endl;
		SqList L1,L2,out;
		InitList_Sq(L1);
		InitList_Sq(L2);
		InitList_Sq(out);
		cin >> order;
		if (order == 1) {
			cout << "Plus_vector Mode On, please enter your first vector length." << endl;
			cin >> length21;
			cout << "Please enter your second vector length." << endl;
			cin >> length22;
			cout << "Please enter your first vector." << endl;
			for (int i = 0; i < length21; i++) {
				cin >> tmp;
				Put(L1, L1.length, tmp);
			}
			cout << "Please enter your second vector." << endl;
			for (int i = 0; i < length22; i++) {
				cin >> tmp;
				Put(L2, L2.length, tmp);
			}
			Plus_vector(L1, L2, out);
			cout << "Result is below." << endl;
			Display_Sq(out);
		}
		else if (order == 2) {
			cout << "Plus_polynomial Mode On, please enter your first poly length." << endl;
			cin >> length21;
			cout << "Please enter your second poly length." << endl;
			cin >> length22;
			cout << "Please enter your first poly." << endl;
			for (int i = 0; i < length21; i++) {
				cin >> tmp;
				Put(L1, L1.length, tmp);
			}
			cout << "Please enter your second poly." << endl;
			for (int i = 0; i < length22; i++) {
				cin >> tmp;
				Put(L2, L2.length, tmp);
			}
			Plus_poly(L1, L2, out);
			cout << "Result is below." << endl;
			Display_Pl(out);
		}
		DestroyList_Sq(L1);
		DestroyList_Sq(L2);
		DestroyList_Sq(out);
		break;
	case 3:
		cout << "Minus Mode On, please enter your type. 1=vector,2=polynomial" << endl;
		SqList L31, L32, out3;
		InitList_Sq(L31);
		InitList_Sq(L32);
		InitList_Sq(out3);
		cin >> order;
		if (order == 1) {
			cout << "Minus_vector Mode On, please enter your first vector length." << endl;
			cin >> length21;
			cout << "Please enter your second vector length." << endl;
			cin >> length22;
			cout << "Please enter your first vector." << endl;
			for (int i = 0; i < length21; i++) {
				cin >> tmp;
				Put(L31, L31.length, tmp);
			}
			cout << "Please enter your second vector." << endl;
			for (int i = 0; i < length22; i++) {
				cin >> tmp;
				Put(L32, L32.length, tmp);
			}
			Minus_vector(L31, L32, out3);
			cout << "Result is below." << endl;
			Display_Sq(out3);
		}
		else if (order == 2) {
			cout << "Minus_polynomial Mode On, please enter your first poly length." << endl;
			cin >> length21;
			cout << "Please enter your second poly length." << endl;
			cin >> length22;
			cout << "Please enter your first poly." << endl;
			for (int i = 0; i < length21; i++) {
				cin >> tmp;
				Put(L31, L31.length, tmp);
			}
			cout << "Please enter your second poly." << endl;
			for (int i = 0; i < length22; i++) {
				cin >> tmp;
				Put(L32, L32.length, tmp);
			}
			Minus_poly(L31, L32, out3);
			cout << "Result is below." << endl;
			Display_Pl(out3);
		}
		DestroyList_Sq(L31);
		DestroyList_Sq(L32);
		DestroyList_Sq(out3);
		break;
	case 4:
		SqList L41, L42;
		double out4;
		InitList_Sq(L41);
		InitList_Sq(L42);
		cout << "Cosine_vector Mode On, please enter your first vector length." << endl;
		cin >> length21;
		cout << "Please enter your second vector length." << endl;
		cin >> length22;
		cout << "Please enter your first vector." << endl;
		for (int i = 0; i < length21; i++) {
			cin >> tmp;
			Put(L41, L41.length, tmp);
		}
		cout << "Please enter your second vector." << endl;
		for (int i = 0; i < length22; i++) {
			cin >> tmp;
			Put(L42, L42.length, tmp);
		}
		Cos_vector(L41, L42, out4);
		cout << "Cosine is " << out4 << "." <<endl;
		DestroyList_Sq(L41);
		DestroyList_Sq(L42);
		break;
	case 5:
		SqList L51, L52,out5;
		InitList_Sq(L51);
		InitList_Sq(L52);
		InitList_Sq(out5);
		cout << "TimesPoly Mode On, please enter your first poly length." << endl;
		cin >> length21;
		cout << "Please enter your second poly length." << endl;
		cin >> length22;
		cout << "Please enter your first poly." << endl;
		for (int i = 0; i < length21; i++) {
			cin >> tmp;
			Put(L51, L51.length, tmp);
		}
		cout << "Please enter your second poly." << endl;
		for (int i = 0; i < length22; i++) {
			cin >> tmp;
			Put(L52, L52.length, tmp);
		}
		Times_poly(L51, L52, out5);
		cout << "Result is below." << endl;
		Display_Pl(out5);
		DestroyList_Sq(L51);
		DestroyList_Sq(L52);
		DestroyList_Sq(out5);
		break;
	case 6:
		cout << "Derivate Mode On, please enter your SqList." << endl;
		SqList L6,out6;
		InitList_Sq(L6);
		InitList_Sq(out6);
		cout << "Enter the length." << endl;
		cin >> length;
		cout << "Enter the " << length << " elements." << endl;
		for (int i = 0; i < length; i++) {
			cin >> tmp;
			Put(L6, L6.length, tmp);
		}
		Derivate_poly(L6, out6);
		cout << "Result is below." << endl;
		Display_Pl(out6);
		DestroyList_Sq(L6);
		DestroyList_Sq(out6);
		break;
	default:
		break;
	}

	
	return 0;
}

int main() {
	CalExpression();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
