#include <iostream>
using namespace std;

struct Node {
	//Vung thong tin
	int info;
	//Vung lien ket
	Node* next;
};

struct CircularLinkedList {
	Node* head;
	Node* tail;
};

//Khoi tao rong
void init(CircularLinkedList &l) {
	l.head = nullptr;
	l.tail = nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}
void addHead(CircularLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.head == nullptr) {
		p->next = p;
		l.head = p;
		l.tail = p;
	}
	else {
		p->next = l.head;
		l.head = p;
		l.tail->next = l.head;
	}
}

//Xuat danh sach ra man hinh
void printList(CircularLinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;
	while (p->next != l.head) {
		cout << p->info << " ";
		p = p->next;
	}

	cout << p->info << endl;
}
//Xoa phan tu dau danh sach
void delHead(CircularLinkedList &l) {
	if (l.head == nullptr)
		return;

	Node* p = l.head;
	l.head = l.head->next;
	
	if (l.head == p) {
		l.head = nullptr;
		l.tail = nullptr;
	}
	else
		l.tail->next = l.head;

	p->next = nullptr;
	delete p;
}
//Giai phong vung nho
void destroyList(CircularLinkedList& l) {
	while (l.head != nullptr) {
		delHead(l);
	}
}

int main() {
	CircularLinkedList l;
	init(l);

	addHead(l, 2);
	addHead(l, 4);
	addHead(l, 5);
	addHead(l, 7);

	printList(l);

	destroyList(l);
	return 0;
}