#include <iostream>
using namespace std;

struct Term {
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

//Khoi tao danh sach rong
void init(LinkedList& l) {
	l.head = nullptr;
}

bool isEmpty(LinkedList l) {
	return l.head == nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(Term x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, Term x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

//Them vao cuoi danh sach
void addTail(LinkedList& l, Term x) {
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

ostream& operator<<(ostream& out, const Term &t) {
	out << t.coef;
	if (t.exp != 0) {
		out << "x^" << t.exp;
	}
	return out;
}

//Duyet danh sach
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
			cout << " + ";
	}

	cout << endl;
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

//Tim kiem phan tu key
Node* search(LinkedList l, int key) {
	Node* q = l.head;

	while (q != nullptr) {
		if (q->info.exp == key)
			return q;
		q = q->next;
	}

	return nullptr;
}

//Them phan tu x vao danh sach sau phan tu mang gia key
void insertAfter(LinkedList l, Term x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Them phan tu x vao danh sach truoc phan tu mang gia key
void insertBefore(LinkedList& l, Term x, int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.exp != key) {
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
void insertOrdered(LinkedList& l, Term x) {
	if (isEmpty(l) || x.exp > l.head->info.exp) {
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

//Sap xep danh sach lien ket
int cmpAsc(Node* a, Node* b) {
	return a->info.exp - b->info.exp;
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

	cout << "================TINH GIA TRI BIEU THUC===================\n";
	cout << "Ket qua: " << calExp(l, 2) << endl;

	destroyList(l);
	return 0;
}