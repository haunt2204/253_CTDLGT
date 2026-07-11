#include <iostream>
using namespace std;

struct Node {
	//Vung thong tin
	int info;
	//Vung lien ket
	Node* next;
};

struct LinkedList {
	Node* head;
};

//Khoi tao danh sach rong
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

//Them vao cuoi danh sach
void addTail(LinkedList& l, int x) {
	Node* p = createNode(x);
	if (isEmpty(l))
		l.head = p;
	else
	{
		Node* q = l.head;
		while (q->next != nullptr) {
			q = q->next;
		}
		q->next = p;
	}
}

void delTail(LinkedList& l) {
	if (isEmpty(l))
		return;

	Node* q = l.head;
	Node* prev = nullptr;
	while (q->next != nullptr) {
		prev = q;
		q = q->next;
	}

	if (prev == nullptr)
		l.head = nullptr;
	else
		prev->next = nullptr;

	delete q;
}

//Duyet danh sach
void printList(LinkedList l) {
	if (isEmpty(l)) {
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

//Tim kiem phan tu key
Node* search(LinkedList l, int key) {
	Node* q = l.head;

	while (q != nullptr) {
		if (q->info == key)
			return q;
		q = q->next;
	}

	return nullptr;
}

//Them phan tu x vao danh sach sau phan tu mang gia key
void insertAfter(LinkedList l, int x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Them phan tu x vao danh sach truoc phan tu mang gia key
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
	p->next = q;
	if (prev != nullptr) {
		prev->next = p;
	}
	else {
		l.head = p;
	}
}

//Them vao danh sach da co thu tu
void insertOrdered(LinkedList& l, int x) {
	if (isEmpty(l) || x < l.head->info) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;

	while (q->next != nullptr && q->next->info < x) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Sap xep danh sach lien ket
int cmpAsc(Node* a, Node* b) {
	return a->info - b->info;
}

void sortList(LinkedList l, int func(Node*, Node*)) {
	if (isEmpty(l))
		return;

	for (Node* i = l.head; i->next != nullptr; i = i->next) {
		for (Node* j = i->next; j != nullptr; j = j->next) {
			if (func(j, i) < 0)
				swap(i->info, j->info);
		}
	}
}

//Truy xuat phan tu thu i
Node* getNodeAt(LinkedList l, int index) {
	if (isEmpty(l) || index < 0)
		return nullptr;

	Node* q = l.head;
	int i = 0;
	while (q != nullptr && i < index) {
		q = q->next;
		i++;
	}

	return q;
}

//Xoa phan tu dau danh sach
void delHead(LinkedList& l) {
	if (!isEmpty(l)) {
		Node* q = l.head;
		l.head = l.head->next;
		q->next = nullptr;
		delete q;
	}
}

//Giai phong vung nho
void destroyList(LinkedList& l) {
	while (!isEmpty(l)) {
		delHead(l);
	}
}

int main() {
	LinkedList l;
	init(l);

	addHead(l, 5);
	addHead(l, 7);
	addHead(l, 4);


	printList(l);

	cout << "============================TIM KIEM================\n";
	Node* res = search(l, 7);

	if (res != nullptr) {
		cout << "Ket qua: " << res->info << endl;
	}
	else
		cout << "Khong tim thay!\n";

	cout << "============================THEM SAU================\n";
	insertAfter(l, 6, 7);
	printList(l);

	cout << "============================THEM CUOI================\n";
	addTail(l, 9);
	printList(l);

	cout << "============================XOA CUOI================\n";
	delTail(l);
	printList(l);

	cout << "============================THEM TRUOC================\n";
	insertBefore(l, 1, 5);
	printList(l);

	cout << "============================SAP XEP================\n";
	//sortList(l, [](Node* a, Node* b) {return -(a->info - b->info); });
	sortList(l, cmpAsc);
	printList(l);

	cout << "============================TRUY XUAT================\n";
	cout << getNodeAt(l, 2)->info << endl;

	cout << "============================THEM VAO DANH CO THU TU================\n";
	insertOrdered(l, 4);
	printList(l);

	destroyList(l);
	return 0;
}
