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

//Khoi tao rong
void init(LinkedList& l) {
	l.head = NULL;
}

//Kiem tra danh sach rong?
bool isEmpty(LinkedList l) {
	return l.head == NULL;
}

//Them phan tu vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, int x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

//Duyet danh sach xuat ra man hinh
void printList(LinkedList l) {
	if (isEmpty(l)) {
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
//Tim 1 phan tu trong danh sach
Node* search(LinkedList l, const int key) {
	Node* p = l.head;

	while (p != nullptr) {
		if (p->info == key)
			return p;
		p = p->next;
	}

	return nullptr;
}

void insertAfter(LinkedList l, const int x, const int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertBefore(LinkedList &l, const int x, const int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info != key) {
		prev = q;
		q = q->next;
	}

	//Khong tim thay
	if (q == nullptr)
		return;

	Node* p = createNode(x);
	p->next = q;
	if (prev == nullptr) {
		l.head = p;
	}
	else {
		prev->next = p;
	}
}

//Them phan tu vao cuoi danh sach
void addTail(LinkedList& l, int x) {
	Node* p = createNode(x);
	if (isEmpty(l)) {
		l.head = p;
		return;
	}

	Node* q = l.head;
	while (q->next != nullptr) {
		q = q->next;
	}

	q->next = p;
}

//Them vao danh sach da co thu tu
void insertOrdered(LinkedList& l, int x) {
	if (isEmpty(l) || l.head->info > x) {
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

//Xoa phan tu dau danh sach
void delHead(LinkedList& l) {
	if (!isEmpty(l)) {
		Node* p = l.head;
		l.head = p->next;
		p->next = nullptr;
		delete p;
	}
}

//Xoa phan tu cuoi danh sach
void delTail(LinkedList& l) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q->next != nullptr) {
		prev = q;
		q = q->next;
	}

	if (prev != nullptr) {
		prev->next = nullptr;
	}
	else {
		l.head = nullptr;
	}

	delete q;
}

//Thao tac sap xep
int cmpAsc(Node* a, Node* b) {
	return a->info - b->info;
}

void sortList(LinkedList l, int func(Node*, Node*)=cmpAsc) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next != nullptr; i=i->next) {
			for (Node* j = i->next; j != nullptr; j=j->next) {
				if (func(j, i) < 0)
					swap(i->info, j->info);
			}
		}
	}
}

//Truy xuat phan tu thu i trong danh sach
Node* getNodeAt(LinkedList l, int index) {
	if (index < 0 || isEmpty(l))
		return nullptr;

	int i = 0;
	Node* p = l.head;
	while (p != nullptr && i < index) {
		i++;
		p = p->next;
	}

	return p;
}

//Giai phong vung nho
void destroyList(LinkedList& l) {
	while (!isEmpty(l)) {
		delTail(l);
	}
}

int main() {
	LinkedList l;
	init(l);

	addHead(l, 9);
	addHead(l, 8);
	addHead(l, 5);
	addHead(l, 1);

	printList(l);

	cout << "=====================TIM KIEM=================\n";
	Node *res = search(l, 4);
	if (res != nullptr)
		cout << "Ket qua: " << res->info << endl;
	else
		cout << "Khong tim thay!\n";

	cout << "=====================THEM SAU=================\n";
	insertAfter(l, 4, 9);
	printList(l);

	cout << "=====================THEM TRUOC=================\n";
	insertBefore(l, 3, 4);
	printList(l);

	cout << "=====================THEM CUOI=================\n";
	addTail(l, 10);
	printList(l);

	cout << "=====================SAP XEP=================\n";
	//sortList(l, cmpAsc);
	sortList(l, [](Node* a, Node* b) {return -(a->info - b->info); });
	printList(l);

	cout << "=====================TRUY CAP PHAN TU THU I=================\n";
	cout << getNodeAt(l, 2)->info << endl;


	//insertOrdered(l, 100);
	printList(l);

	destroyList(l);
	printList(l);
	return 0;
}