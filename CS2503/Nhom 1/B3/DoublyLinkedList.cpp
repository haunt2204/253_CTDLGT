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

//Thao tac them vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node();
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

//Thao tac them vao cuoi danh sach
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

//Tim kiem phan tu key
Node* search(DoublyLinkedList l, const int &key) {
	Node* q = l.head;
	while (q != nullptr) {
		if (q->info == key)
			return q;
		q = q->next;
	}
	return q;
}

//Them phan tu x vao phia sau phan tu mang gia tri key
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

//Duyet danh sach
void printListFromHead(DoublyLinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = l.head;
	while (p != nullptr) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}

void printListFromTail(DoublyLinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = l.tail;
	while (p != nullptr) {
		cout << p->info << " ";
		p = p->prev;
	}
	cout << endl;
}

//Xoa dau
void delHead(DoublyLinkedList& l) {
	if (l.head == nullptr)
		return;
	Node* p = l.head;

	l.head = l.head->next;

	if (l.head != nullptr) {
		l.head->prev = nullptr;
	}
	else
		l.tail = nullptr;

	p->next = nullptr;
	delete p;
}

//Xoa cuoi
void delTail(DoublyLinkedList& l) {
	if (l.head == nullptr)
		return;
	Node* p = l.tail;

	l.tail = l.tail->prev;

	if (l.tail != nullptr) {
		l.tail->next = nullptr;
	}
	else
		l.head = nullptr;

	p->prev = nullptr;
	delete p;
}

//Giai phong vung nho
void destroyList(DoublyLinkedList& l) {
	while (l.head!=nullptr) {
		delHead(l);
	}
}

int main() {
	DoublyLinkedList l;
	init(l);
	addHead(l, 4);
	addHead(l, 5);
	addHead(l, 2);
	printListFromHead(l);
	addTail(l, 9);
	cout << "==================THEM SAU================\n";
	insertAfter(l, 3, 9);
	printListFromHead(l);
	destroyList(l);
	printListFromTail(l);
	return 0;
}