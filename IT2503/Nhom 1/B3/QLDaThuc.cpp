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

struct LinkedList
{
	Node* head;
};

//Khoi tao rong
void init(LinkedList& l) {
	l.head = NULL;
}

//Kiem tra rong
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

//Them cuoi danh sach
void addTail(LinkedList& l, Term x) {
	Node* p = createNode(x);
	if (isEmpty(l)) {
		l.head = p;
	}
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
	if (!isEmpty(l)) {
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
}

//Tham phan tu vao truoc phan tu mang gia tri key
void insertBefore(LinkedList& l, Term x, int key) {
	if (isEmpty(l))
		return;

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
	if (prev == nullptr) {
		l.head = p;
	}
	else {
		prev->next = p;
	}
}

//Thao tac tim kiem phan tu key trong danh
Node* search(LinkedList l, int key) {
	Node* p = l.head;
	while (p != nullptr) {
		if (p->info.exp == key)
			return p;
		p = p->next;
	}
	return p;
}

//Thao tac them vao sau phan tu key 1 gia tri x
void insertAfter(LinkedList l, Term x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Sap xep danh sach
int cmpAsc(Node* a, Node* b) {
	return a->info.exp - b->info.exp;
}

void sortList(LinkedList l, int func(Node*, Node*)) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next != nullptr; i = i->next) {
			for (Node* j = i->next; j != nullptr; j = j->next) {
				if (func(j, i) < 0)
					swap(i->info, j->info);
			}
		}
	}
}

//Truy xuat phan tu thu i trong danh sach
Node* getNodeAt(LinkedList l, int index) {
	//index = 2
	if (isEmpty(l))
		return nullptr;
	Node* q = l.head;
	int i = 0;
	while (q != nullptr && i < index) {
		q = q->next;
		i++;
	}

	return q;
}

//Them phan tu vao danh sach van dam bao thu tu tang dan
void insertOrdered(LinkedList& l, Term x) {
	if (isEmpty(l) || l.head->info.exp < x.exp) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;
	while (q->next != nullptr && q->info.exp > x.exp) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

ostream& operator<<(ostream& out, Term p) {
	out << p.coef;
	if (p.exp != 0)
		out << "x^" << p.exp;
	return out;
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

//Duyet danh sach lien ket va in ra man hinh
void printList(LinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = l.head;
	while (p != nullptr) {
		
		cout << p->info;
		p = p->next;
		if(p)
			cout << " + ";
	}
	cout << endl;
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

	cout << "=================TINH GIA TRI DA THUC================\n";
	cout << "Ket qua: " << calExp(l, 2) << endl;

	destroyList(l);
	//printList(l);
	return 0;
}