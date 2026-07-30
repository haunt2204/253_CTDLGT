#include "Stack.h"
#include <stack>

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