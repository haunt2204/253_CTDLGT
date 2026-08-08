#include <iostream>
using namespace std;

#define MAX 50

struct Stack
{
	int a[MAX];
	int top;
};

//Khoi tao rong
void init(Stack& s) {
	s.top = -1;
}

//Kiem tra stack rong
bool isEmpty(Stack s) {
	return s.top == -1;
}
//Kiem tra stack day
bool isFull(Stack s) {
	return s.top == MAX - 1;
}
//Them phan tu vao stack
void push(Stack& s, int x) {
	if (!isFull(s)) {
		s.a[++s.top] = x;
	}
}
//Lay phan tu tren dinh stack
int top(Stack s) {
	return s.a[s.top];
}
//Xoa phan tu khoi stack
void pop(Stack& s) {
	if (!isEmpty(s)) {
		s.top--;
	}
}