#include <iostream>
using namespace std;

struct Node
{
	int info;
	Node* next, * prev;
};

struct DoublyLinkedList
{
	Node* head, * tail;
};

//Khoi tao rong
void init(DoublyLinkedList& l) {
	l.head = nullptr;
	l.tail = nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}

void addHead(DoublyLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.head == nullptr) {
		l.tail = p;
	}
	else {
		p->next = l.head;
		l.head->prev = p;
	}
	l.head = p;
}

//Them phan tu vao cuoi danh sach
void addTail(DoublyLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.tail == nullptr) {
		l.head = p;
	}
	else {
		p->prev = l.tail;
		l.tail->next = p;
	}
	l.tail = p;
}

//Duyet danh sach
void printListFromHead(DoublyLinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* q = l.head;
	while (q != nullptr) {
		cout << q->info << " ";
		q = q->next;
	}
	cout << endl;
}

void printListFromTail(DoublyLinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* q = l.tail;
	while (q != nullptr) {
		cout << q->info << " ";
		q = q->prev;
	}
	cout << endl;
}

//Tim phan tu: mang gia tri key, min, max
Node* search(DoublyLinkedList l, const int key) {
	Node* q = l.tail;
	while (q != nullptr) {
		if (q->info == key)
			return q;
		q = q->prev;
	}
	return nullptr;
}

bool max(int a, int b) {
	return a > b;
}

bool min(int a, int b) {
	return a < b;
}

Node* findExtrem(DoublyLinkedList l, bool func(int, int)) {
	if (l.head == nullptr)
		return nullptr;

	Node* res = l.head;
	Node* q = l.head->next;

	while (q != nullptr) {
		if (func(q->info, res->info))
			res = q;
		q = q->next;
	}

	return res;
}

//Them phan tu x phia sau phan tu mang gia tri key
void insertAfter(DoublyLinkedList l, int x, int key) {
	Node* q = search(l, key);

	if (q == nullptr)
		return;

	if (q == l.tail) {
		addTail(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* qNext = q->next;

	p->next = qNext;
	qNext->prev = p;

	p->prev = q;
	q->next = p;
}

//Xoa phan tu dau danh sach
void delHead(DoublyLinkedList& l) {
	if (l.head == nullptr)
		return;
	Node* p = l.head;

	l.head = l.head->next;
	if (l.head != nullptr)
		l.head->prev = nullptr;
	else
		l.tail = nullptr;

	p->next = nullptr;
	delete p;
}

//Xoa phan tu cuoi danh sach
void delTail(DoublyLinkedList& l) {
	if (l.head == nullptr)
		return;
	Node* p = l.tail;

	l.tail = l.tail->prev;
	if (l.tail != nullptr)
		l.tail->next = nullptr;
	else
		l.head = nullptr;

	p->prev = nullptr;
	delete p;
}

//Giai phong vung nho
void destroyList(DoublyLinkedList& l) {
	while (l.head != nullptr) {
		delTail(l);
	}
}

int main() {
	DoublyLinkedList l;
	init(l);

	addHead(l, 6);
	addHead(l, 2);
	addHead(l, 3);
	printListFromHead(l);

	cout << "==============TIM KIEM=============\n";
	cout << "Ket qua: " << search(l, 2)->info << endl;
	cout << "Max: " << findExtrem(l, max)->info << endl;
	cout << "Min: " << findExtrem(l, min)->info << endl;

	cout << "==============THEM SAU=============\n";
	insertAfter(l, 999, 6);
	printListFromHead(l);
	
	destroyList(l);
	printListFromTail(l);
	return 0;
}