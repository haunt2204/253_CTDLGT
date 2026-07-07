#include <iostream>
using namespace std;

struct Node
{
	//Vung thong tin
	int info;
	//Vung lien ket
	Node* next;
};

struct LinkedList
{
	Node* head;
};

void init(LinkedList& l) {
	l.head = nullptr;
}

bool isEmpty(LinkedList l) {
	return l.head == nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, int x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* q = l.head;
	while (q != nullptr) {
		cout << q->info;
		q = q->next;
		if(q)
			cout << "->";
	}
	cout << endl;
}

//Tim kiem
Node* search(LinkedList l, const int key) {
	Node* q = l.head;
	while (q != nullptr) {
		if (q->info == key)
			return q;
		q = q->next;
	}
	return q;
}


//Them phan tu x vao sau phan tu key
void insertAfter(LinkedList l, int x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(LinkedList& l, int x) {
	if (isEmpty(l) || x < l.head->info) {
		addHead(l, x);
		return;
	}
	Node* p = createNode(x);
	Node* q = l.head;

	while (q->next !=nullptr && q->next->info < x) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Them 1 phan tu x vao phia truoc phan tu key
void insertBefore(LinkedList& l, int x, int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info != key) {
		prev = q;
		q = q->next;
	}

	if (q == nullptr)
		return;

	Node* p = createNode(x);

	if (prev != nullptr) {
		p->next = q;
		prev->next = p;
	}
	else {
		p->next = l.head;
		l.head = p;
	}
}

//Sap xep danh sach lien ket
void sortList(LinkedList l) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next != nullptr; i=i->next) {
			for (Node* j = i->next; j != nullptr; j = j->next) {
				if (j->info < i->info)
					swap(i->info, j->info);
			}
		}
	}
}

//Truy xuat phan tu thu i trong danh sach
Node* getNodeAt(LinkedList l, int index) {
	if (isEmpty(l) || index < 0)
		return nullptr;

	Node* q = l.head;
	int i = 0;
	while (q != nullptr && i<index) {
		q = q->next;
		i++;
	}
	return q;
}

//Them phan tu vao cuoi danh sach
void addTail(LinkedList& l, int x) {
	Node* p = createNode(x);
	if (isEmpty(l)) {
		l.head = p;
		return;
	}

	Node* q = l.head;
	while (q->next!=nullptr) {
		q = q->next;
	}

	q->next = p;
}

//Xoa phan tu o dau danh sach
void delHead(LinkedList& l) {
	if (!isEmpty(l)) {
		Node* q = l.head;
		l.head = l.head->next;

		q->next = nullptr;
		delete q;
	}
}

//Xoa phan tu cuoi danh sach
void delTail(LinkedList& l) {
	if (isEmpty(l))
		return;

	Node* q = l.head;
	Node* prev = NULL;

	while (q->next != nullptr) {
		prev = q;
		q = q->next;
	}

	if (prev != nullptr)
		prev->next = nullptr;
	else
		l.head = nullptr;

	delete q;
}

//Giai phong danh sach
void destroyList(LinkedList& l) {
	while (!isEmpty(l)) {
		delTail(l);
	}
}

int main() {
	LinkedList l;
	init(l);

	addHead(l, 3);
	addHead(l, 4);
	addTail(l, 9);
	printList(l);

	cout << "==================TIM KIEM==============\n";
	Node *res = search(l, 3);

	if (res != nullptr)
		cout << "Ket qua: " << res->info << endl;
	else
		cout << "Khong tim thay!\n";

	cout << "==================THEM SAU==============\n";
	insertAfter(l, 6, 3);
	printList(l);

	cout << "==================THEM TRUOC==============\n";
	insertBefore(l, 2, 4);
	printList(l);

	cout << "==================SAP XEP==============\n";
	sortList(l);
	printList(l);

	cout << "==================TRUY XUAT PHAN TU==============\n";
	cout << "Ket qua: " << getNodeAt(l, 3)->info << endl;

	cout << "==================THEM CO THU TU==============\n";
	insertOrdered(l, 5);
	printList(l);

	destroyList(l);
	//printList(l);
	return 0;
}