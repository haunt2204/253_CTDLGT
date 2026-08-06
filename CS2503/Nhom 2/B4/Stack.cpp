#include <iostream>
#include <stack>
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

//Kiem tra rong
bool isEmpty(Stack s) {
	return s.top == -1;
}

//Kiem tra day
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

//Xoa phan tu tren dinh stack
void pop(Stack& s) {
	if (!isEmpty(s)) {
		s.top--;
	}
}

//Chuyen doi so
void convert(int n) {
	/*Stack s;
	init(s);*/
	stack<int> s;

	while (n > 0) {
		/*push(s, n % 2);*/
		s.push(n % 2);
		n = n / 2;
	}

	while (!s.empty()) {
		/*cout << top(s);*/
		cout << s.top();
		/*pop(s);*/
		s.pop();
	}
	cout << endl;
}

int main() {
	Stack s;
	init(s);

	push(s, 9);
	push(s, 1);
	push(s, 3);

	while (!isEmpty(s)) {
		cout << top(s) << endl;
		pop(s);
	}

	convert(10);

	return 0;
}