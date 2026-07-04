#include <iostream>
using namespace std;

//2 5 4 7 1
struct Node {
	//Vung thong tin
	int info;

	//Vung lien ket
	Node* next;
};

struct LinkedList
{
	Node* head;
};

//Khoi tao rong
void init(LinkedList &l) {
	l.head = NULL;
}

//Kiem tra rong
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

//Them cuoi danh sach
void addTail(LinkedList &l, int x) {
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
void insertBefore(LinkedList &l, int x, int key) {
	if (isEmpty(l))
		return;

	Node* q = l.head;
	Node* prev = nullptr;
	while (q != nullptr && q->info!=key) {
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
		if (p->info == key)
			return p;
		p = p->next;
	}
	return p;
}

//Thao tac them vao sau phan tu key 1 gia tri x
void insertAfter(LinkedList l, int x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Sap xep danh sach
int cmpAsc(Node* a, Node* b) {
	return a->info - b->info;
}

void sortList(LinkedList l, int func(Node*, Node*)) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next!=nullptr; i=i->next) {
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
void insertOrdered(LinkedList& l, int x) {
	if (isEmpty(l) || l.head->info > x) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;
	while (q->next != nullptr && q->info < x) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}


//Duyet danh sach lien ket va in ra man hinh
void printList(LinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = l.head;
	while (p!=nullptr) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}

//Xoa phan tu dau danh sach
void delHead(LinkedList &l) {
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

	addHead(l, 4);
	addHead(l, 5);
	addHead(l, 3);
	addHead(l, 1);
	addTail(l, 2);
	printList(l);

	cout << "==========================TIM KIEM====================\n";
	Node*res = search(l, 2);
	if (res != nullptr) {
		cout << "Ket qua: " << res->info << endl;
	}
	else
		cout << "Khong tim thay!\n";

	cout << "==========================THEM SAU====================\n";
	insertAfter(l, 6, 1);
	printList(l);

	cout << "==========================THEM TRUOC====================\n";
	insertBefore(l, 7, 4);
	printList(l);

	cout << "==========================SAP XEP====================\n";
	/*sortList(l, cmpAsc);*/
	sortList(l, [](Node* a, Node* b) {return -(a->info - b->info); });
	printList(l);

	cout << "==========================TRUY XUAT PHAN TU====================\n";
	cout << "Ket qua: " << getNodeAt(l, 3)->info << endl;

	cout << "==========================THEM VAO DS CO THU TU====================\n";
	//insertOrdered(l, 2);
	printList(l);

	destroyList(l);
	//printList(l);
	return 0;
}