#include <iostream>
#include <stack>
using namespace std;

#define MAX 50

struct Stack
{
	int a[MAX];
	int top;
};

void init(Stack& s) {
	s.top = -1;
}

//Kiem tra stack rong
bool isEmpty(Stack s) {
	return s.top == -1;
}

//Kiem tra stack day
bool isFull(Stack s) {
	return s.top == MAX-1;
}

//Them phan tu vao stack
void push(Stack& s, int x) {
	if (!isFull(s)) {
		s.a[++s.top] = x;
	}
}

//Lay phan tu tren dinh stack
int get(Stack s) {
	return s.a[s.top];
}

//Xoa phan tu o dinh stack
void pop(Stack& s) {
	if (!isEmpty(s)) {
		s.top--;
	}
}

void convert(int n) {
	/*Stack s;
	init(s);*/
	stack<int>s;

	while (n != 0) {
		/*push(s, n % 2);*/
		s.push(n % 2);
		n = n / 2;
	}

	while (!s.empty()) {
		//cout << get(s);
		cout << s.top();
		s.pop();
	}
}

int main() {
	Stack s;
	init(s);

	push(s, 9);
	push(s, 2);
	push(s, 1);

	//In stack ra man hinh
	while (!isEmpty(s)) {
		cout << get(s) << endl;
		pop(s);
	}

	convert(4);

	return 0;
}