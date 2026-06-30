#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct SinhVien {
	int mssv;
	string hoTen;
	char ngaySinh[11];
	char queQuan[100];
	double dtb;
};

void xuat1Sv(SinhVien sv) {
	cout << "===============================\n";
	cout << "ID: ";
	cout << sv.mssv << endl;
	cout << "Ho va ten: ";
	cout << sv.hoTen << endl;
	cout << "Ngay sinh: ";
	cout << sv.ngaySinh << endl;
	cout << "Que quan: ";
	cout << sv.queQuan << endl;
	cout << "Diem trung binh: ";
	cout << sv.dtb << endl;
	cout << "===============================\n";
}

struct Node {
	//Vung thong tin
	SinhVien info;
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
Node* createNode(SinhVien x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void addHead(LinkedList& l, SinhVien x) {
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
		//cout << p->info << " ";
		xuat1Sv(p->info);
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
		if (p->info.mssv == key)
			return p;
		p = p->next;
	}
	return nullptr;
}

//Them 1 phan tu x sau phan tu mang gia tri key
void insertAfter(LinkedList l, SinhVien x, int key) {
	Node* q = search(l, key);

	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(LinkedList& l, SinhVien x) {
	if (isEmpty(l) || l.head->info.mssv > x.mssv) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;

	while (q->next != nullptr && q->next->info.mssv < x.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Them phan tu vao cuoi danh sach
void addTail(LinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	if (isEmpty(l))
		l.head = p;
	else {
		Node* q = l.head;
		while (q->next!=nullptr) {
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
	return a->info.mssv - b->info.mssv;
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
	while (q != NULL && i<index) {
		i++;
		q = q->next;
	}

	return q;
}

//Nhap danh sach tu file
void inputFromFile(LinkedList& l) {
	ifstream fin("SinhVien.txt");

	if (fin.is_open()) {
		SinhVien sv;

		while (!fin.eof()) {
			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			fin.getline(sv.queQuan, 50, '#');
			fin >> sv.dtb;

			addTail(l, sv);
		}

		fin.close();
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
	
	inputFromFile(l);
	printList(l);

	destroyList(l);
	return 0;
}