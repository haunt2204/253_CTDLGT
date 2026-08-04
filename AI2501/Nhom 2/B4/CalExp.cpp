#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <stack>
using namespace std;

int getPriority(string op) {
	if (op == "*" || op == "/")
		return 2;

	if (op == "+" || op == "-")
		return 1;

	return 0;
}

char* infixToPostfix(char* str) {
	int size = strlen(str);
	Queue postfix;
	init(postfix);

	stack<char*> s;

	char* p = strtok(str, " ");
	while (p != nullptr) {
		if (isdigit(*p)) {
			enQueue(postfix, p);
		}
		else if (*p == '(') {
			s.push(p);
		}
		else if (*p == ')') {
			char* op = s.top();
			s.pop();
			while (*op != '(') {
				enQueue(postfix, op);
				op = s.top();
				s.pop();
			}
		}
		else {
			while (!s.empty() && getPriority(p) <= getPriority(s.top())) {
				enQueue(postfix, s.top());
				s.pop();
			}
			s.push(p);
		}
		p = strtok(NULL, " ");
	}

	while (!s.empty()) {
		enQueue(postfix, s.top());
		s.pop();
	}

	char* res = new char[size];
	res[0] = '\0';

	while (!isEmpty(postfix)) {
		strcat(res, deQueue(postfix));
		if(!isEmpty(postfix))
			strcat(res, " ");
	}

	return res;
}

void calExp(char* str) {
	Stack s;
	init(s);
	int a, b;

	char*p = strtok(str, " ");
	while (p != nullptr) {
		if (isdigit(*p)) {
			push(s, atoi(p));
		}
		else {
			b = top(s);//4
			pop(s);

			a = top(s);//2
			pop(s);
			switch (*p)
			{
			case '+':
				push(s, a + b); break;
			case '-':
				push(s, a - b); break;
			case '*':
				push(s, a * b); break;
			case '/':
				if (b == 0) {
					cout << "Loi chia cho 0!\n";
					return;
				}
				push(s, a / b); break;
			default:
				cout << "Phep tinh khong hop le!\n";
				return;
			}
		}
		p = strtok(NULL, " ");
	}

	cout << "Ket qua: " << top(s) << endl;
	pop(s);
}

int main() {
	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";

	/*char str[] = "2 4 + 5 3 - 2 / - 3 + 1 5 * -";

	calExp(str);*/

	char *res = infixToPostfix(str);

	cout << res << endl;
	calExp(res);
	delete[]res;
	return 0;
}