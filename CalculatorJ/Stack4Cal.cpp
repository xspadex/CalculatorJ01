#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

extern short PriorTab[7][7] = { {1,1,0,0,0,1,1},{1,1,0,0,0,1,1},{1,1,1,1,0,1,1},{1,1,1,1,0,1,1},{0,0,0,0,0,2,-1},{1,1,1,1,-1,1,1},{0,0,0,0,0,-1,2} };

SNode* InitSNode(SNode *p) {
	p = (SNode*)malloc(sizeof(SNode));
	p->next = NULL;
	return p;
}

SNode* push(SNode *head,SNode *newNode) {
	newNode->next = head;
	return newNode;
}

short top(SNode *head) {
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