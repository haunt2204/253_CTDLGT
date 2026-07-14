#include <iostream>
using namespace std;

struct Term
{
	float coef;
	int exp;
};

struct Node {
	//Vung thong tin
	Term info;
	//Vung lien ket
	Node* next;
};

struct LinkedList {
	Node* head;
};

//Ham khoi tao rong
void init(LinkedList& l) {
	l.head = nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(Term x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void addHead(LinkedList& l, Term x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

bool isEmpty(LinkedList l) {
	return l.head == NULL;
}

//Duyet danh sach
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "DS rong!\n";
	}
	Node* p = l.head;
	while (p != nullptr) {
		cout << p->info.coef;
		if (p->info.exp != 0)
			cout << "x^" << p->info.exp;
		p = p->next;
		if (p != nullptr)
			cout << " + ";

	}
	cout << endl;
}

//Xoa phan tu dau danh sach
void delHead(LinkedList& l) {
	if (!isEmpty(l)) {
		Node* p = l.head;
		l.head = l.head->next;
		p->next = nullptr;
		delete p;
	}
}

//Thao tac tim kiem 1 phan tu
Node* search(LinkedList l, const int key) {
	Node* p = l.head;
	while (p != nullptr) {
		if (p->info.exp == key)
			return p;
		p = p->next;
	}
	return nullptr;
}

//Them 1 phan tu x sau phan tu mang gia tri key
void insertAfter(LinkedList l, Term x, int key) {
	Node* q = search(l, key);

	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(LinkedList& l, Term x) {
	if (isEmpty(l) || l.head->info.exp < x.exp) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;

	while (q->next != nullptr && q->next->info.exp > x.exp) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Them phan tu vao cuoi danh sach
void addTail(LinkedList& l, Term x) {
	Node* p = createNode(x);
	if (isEmpty(l))
		l.head = p;
	else {
		Node* q = l.head;
		while (q->next != nullptr) {
			q = q->next;
		}

		q->next = p;
	}
}

//Xoa phan tu cuoi danh sach
void delTail(LinkedList& l) {
	if (isEmpty(l))
		return;

	Node* q = l.head;
	Node* prev = nullptr;

	while (q->next != NULL) {
		prev = q;
		q = q->next;
	}

	if (prev == NULL)
		l.head = NULL;
	else
		prev->next = NULL;

	delete q;
}

//Sap xep danh sach
int cmpAsc(Node* a, Node* b) {
	return a->info.exp - b->info.exp;
}
void sortList(LinkedList& l, int func(Node*, Node*)) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next != NULL; i = i->next) {
			for (Node* j = i->next; j != NULL; j = j->next) {
				if (func(j, i) < 0)
					swap(i->info, j->info);
			}
		}
	}
}

double calExp(LinkedList l, double x) {
	double res = 0;
	Node* q = l.head;

	while (q != nullptr) {
		res += q->info.coef * pow(x, q->info.exp);
		q = q->next;
	}

	return res;
}

//Truy cap phan tu thu i trong danh sach
Node* getNodeAt(LinkedList& l, int index) {
	if (index < 0 || isEmpty(l))
		return nullptr;

	//index = 2
	Node* q = l.head;
	int i = 0;
	while (q != NULL && i < index) {
		i++;
		q = q->next;
	}

	return q;
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
	
	Term t1, t2, t3;

	t1.coef = 2;
	t1.exp = 2;
	insertOrdered(l, t1);

	t2.coef = 2;
	t2.exp = 3;
	insertOrdered(l, t2);

	t3.coef = 1;
	t3.exp = 0;
	insertOrdered(l, t3);

	printList(l);

	cout << "Ket qua: " << calExp(l, 1) << endl;

	destroyList(l);
	return 0;
}