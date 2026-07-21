#include <iostream>
using namespace std;

struct Term
{
	float coef;
	int exp;
};

struct Node
{
	//Vung thong tin
	Term info;
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

ostream& operator<< (ostream& out, const Term &t) {
	out << t.coef;
	if (t.exp != 0) {
		out << "x^" << t.exp;
	}
	return out;
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
		if (q)
			cout << " + ";
	}
	cout << endl;
}

//Tinh gia tri da thuc
double calExp(LinkedList l, float x) {
	double res = 0;

	Node* q = l.head;
	while (q != nullptr) {
		res += q->info.coef * pow(x, q->info.exp);
		q = q->next;
	}

	return res;
}

//Tim kiem
Node* search(LinkedList l, const int key) {
	Node* q = l.head;
	while (q != nullptr) {
		if (q->info.exp == key)
			return q;
		q = q->next;
	}
	return q;
}


//Them phan tu x vao sau phan tu key
void insertAfter(LinkedList l, Term x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

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

//Them 1 phan tu x vao phia truoc phan tu key
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
		for (Node* i = l.head; i->next != nullptr; i = i->next) {
			for (Node* j = i->next; j != nullptr; j = j->next) {
				if (j->info.exp < i->info.exp)
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
	while (q != nullptr && i < index) {
		q = q->next;
		i++;
	}
	return q;
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

istream& operator>>(istream& in, Term& t) {
	cout << "He so: ";
	in >> t.coef;
	cout << "Bac: ";
	in >> t.exp;
	return in;
}

int main() {
	LinkedList l;
	init(l);

	Term t1, t2, t3;

	/*cin >> t1;*/
	t1.coef = 3;
	t1.exp = 2;
	insertOrdered(l, t1);

	t2.coef = 2;
	t2.exp = 3;
	insertOrdered(l, t2);

	t3.coef = 1;
	t3.exp = 0;
	insertOrdered(l, t3);

	printList(l);

	cout << "=============TINH GIA TRI BIEU THUC===========\n";
	cout << "Ket qua: " << calExp(l, 2) << endl;

	destroyList(l);
	//printList(l);
	return 0;
}