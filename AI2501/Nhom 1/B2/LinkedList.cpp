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

//Ham khoi tao rong
void init(LinkedList& l) {
	l.head = nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void addHead(LinkedList& l, int x) {
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
		cout << p->info << " ";
		p = p->next;
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
		if (p->info == key)
			return p;
		p = p->next;
	}
	return nullptr;
}

//Them 1 phan tu x sau phan tu mang gia tri key
void insertAfter(LinkedList l, int x, int key) {
	Node* q = search(l, key);

	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

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

//Them phan tu vao cuoi danh sach
void addTail(LinkedList& l, int x) {
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
	return a->info - b->info;
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
	addHead(l, 3);
	addHead(l, 5);
	addHead(l, 2);
	addHead(l, 7);
	addTail(l, 9);
	printList(l);

	cout << "==================TIM KIEM================\n";
	Node* res = search(l, 3);
	if (res != NULL) {
		cout << "Ket qua: " << res->info << endl;
	}
	else
		cout << "Khong tim thay!";

	cout << "==================THEM SAU PHAN TU KEY================\n";
	insertAfter(l, 6, 7);
	printList(l);

	cout << "==================TRUY CAP PHAN TU I================\n";
	Node* temp = getNodeAt(l, 4);
	if (temp != nullptr) {
		cout << temp->info << endl;
	}
	else
		cout << "Ngoai pham vi!\n";

	cout << "==================XOA PHAN TU CUOI================\n";
	delTail(l);
	printList(l);

	cout << "==================SAP XEP================\n";
	//sortList(l, [](Node* a, Node* b) {return -(a->info - b->info); });
	sortList(l, cmpAsc);
	printList(l);

	cout << "==================THEM PHAN TU VAO DS CO THU TU================\n";
	insertOrdered(l, 4);
	printList(l);

	destroyList(l);
	return 0;
}