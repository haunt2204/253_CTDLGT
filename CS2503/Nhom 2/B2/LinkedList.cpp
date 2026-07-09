#include <iostream>
using namespace std;

//12 5 3 7 5
struct Node {
	//Vung thong tin
	int info;
	//Vung lien ket
	Node* next;
};

struct LinkedList {
	Node* head;
};

//Thao tac khoi tao rong
void init(LinkedList& l) {
	l.head = nullptr;
}

bool isEmpty(LinkedList l) {
	return l.head == nullptr;
}

//Thao tac them phan tu vao dau danh sach
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

//Thao tac duyet danh sach
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;
	while (p!=nullptr){
		cout << p->info << " ";
		p = p->next;
	}

	cout << endl;
}

//Tim kiem phan tu mang gia tri key
Node* search(LinkedList l, int key) {
	Node* p = l.head;
	while (p != nullptr) {
		if (p->info == key)
			return p;
		p = p->next;
	}
	return p;
}

//Them phan tu x vao danh sach phia sau phan tu mang gia tri key
void insertAfter(LinkedList l, int x, int key) {
	Node* q = search(l, key);
	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Them cuoi danh sach
void addTail(LinkedList& l, int x) {
	Node* p = createNode(x);
	if (isEmpty(l)) {
		l.head = p;
	}
	else {
		Node* q = l.head;
		while (q->next!=nullptr) {
			q = q->next;
		}
		q->next = p;
	}
}

//Xoa phan tu cuoi danh
void delTail(LinkedList& l) {
	if (isEmpty(l))
		return;

	Node* q = l.head;
	Node* prev = nullptr;
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

//Thao tac them vao truoc phan tu mang gia tri key
void insertBefore(LinkedList& l, int x, int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info != key) {
		prev = q;
		q = q->next;
	}

	//Truong hop khong tim thay key
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

//Them phan tu vao danh sach co thu tu
void insertOrdered(LinkedList& l, int x) {
	if (isEmpty(l) || x < l.head->info) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;
	while (q->next != nullptr && x > q->next->info) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Thao tac sap xep danh sach lien ket
int cmpAsc(Node* a, Node* b) {
	return a->info - b->info;
}

void sortList(LinkedList l, int func(Node*, Node*)) {
	if (!isEmpty(l)) {
		for (Node* i = l.head; i->next != nullptr; i = i->next) {
			for (Node* j = i->next; j != nullptr; j = j->next) {
				if (func(j, i)<0)
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

//Xoa phan tu dau danh sach
void delHead(LinkedList& l) {
	if (!isEmpty(l)) {
		Node* p = l.head;
		l.head = l.head->next;

		p->next = nullptr;
		delete p;
	}
}



//Giai phong nho
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

	printList(l);

	cout << "==================TIM KIEM================\n";
	Node* res = search(l, 47);

	if (res != nullptr) {
		cout << "Ket qua: " << res->info << endl;
	}
	else
		cout << "Khong tim thay!\n";

	cout << "==================THEM SAU================\n";
	insertAfter(l, 6, 7);
	printList(l);

	cout << "==================THEM CUOI================\n";
	addTail(l, 10);
	printList(l);

	cout << "==================XOA CUOI================\n";
	delTail(l);
	printList(l);

	cout << "==================THEM TRUOC================\n";
	insertBefore(l, 2, 6);
	printList(l);

	cout << "==================TRUY XUAT================\n";
	cout << getNodeAt(l, 2)->info << endl;

	cout << "==================SAP XEP================\n";
	sortList(l, cmpAsc);
	printList(l);

	cout << "==================THEM VAO DS CO THU TU================\n";
	insertOrdered(l, 10);
	printList(l);

	destroyList(l);
	/*printList(l);*/
	return 0;
}