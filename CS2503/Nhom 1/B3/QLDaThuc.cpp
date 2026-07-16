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

//Khoi tao rong
void init(LinkedList& l) {
	l.head = NULL;
}

//Kiem tra danh sach rong?
bool isEmpty(LinkedList l) {
	return l.head == NULL;
}

//Them phan tu vao dau danh sach
Node* createNode(Term x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, Term x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

ostream& operator<<(ostream& out, const Term &t) {
	out << t.coef ;
	if (t.exp != 0)
		cout << "x^" << t.exp;
	return out;
}

//Duyet danh sach xuat ra man hinh
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;

	while (p != nullptr) {
		cout << p->info;
		p = p->next;
		if (p)
			cout << " + ";
	}

	cout << endl;
}

//Tinh gia tri bieu thuc
double calExp(LinkedList l, double x) {
	double res = 0;

	Node* p = l.head;

	while (p != nullptr) {
		res += p->info.coef * pow(x, p->info.exp);
		p = p->next;
	}

	return res;
}

//Tim 1 phan tu trong danh sach
Node* search(LinkedList l, const int key) {
	Node* p = l.head;

	while (p != nullptr) {
		if (p->info.exp == key)
			return p;
		p = p->next;
	}

	return nullptr;
}

void insertAfter(LinkedList l, const Term x, const int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertBefore(LinkedList &l, const Term x, const int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.exp != key) {
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
void addTail(LinkedList& l, Term x) {
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
	return a->info.exp - b->info.exp;
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

	cout << "================TINH GIA TRI BIEU THUC===============\n";
	cout << "Ket qua: " << calExp(l, 2) << endl;

	destroyList(l);
	printList(l);
	return 0;
}