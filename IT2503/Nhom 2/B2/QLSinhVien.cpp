#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SinhVien {
	int mssv;
	string hoTen;
	char ngaySinh[11];
	char queQuan[100];
	double dtb;
};

//Xuat 1 sinh vien
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

//Khoi tao danh sach rong
void init(LinkedList& l) {
	l.head = nullptr;
}

bool isEmpty(LinkedList l) {
	return l.head == nullptr;
}

//Them phan tu vao dau danh sach
Node* createNode(SinhVien x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

//Them vao cuoi danh sach
void addTail(LinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	if (isEmpty(l))
		l.head = p;
	else
	{
		Node* q = l.head;
		while (q->next!=nullptr) {
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

//Duyet danh sach
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* q = l.head;

	while (q != nullptr) {
		xuat1Sv(q->info);
		/*cout << q->info << " ";*/
		q = q->next;
	}

	cout << endl;
}

//Tim kiem phan tu key
Node* search(LinkedList l, int key) {
	Node* q = l.head;

	while (q != nullptr) {
		if (q->info.mssv == key)
			return q;
		q = q->next;
	}

	return nullptr;
}

//Them phan tu x vao danh sach sau phan tu mang gia key
void insertAfter(LinkedList l, SinhVien x, int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Them phan tu x vao danh sach truoc phan tu mang gia key
void insertBefore(LinkedList& l, SinhVien x, int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.mssv != key) {
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
void insertOrdered(LinkedList& l, SinhVien x) {
	if (isEmpty(l) || x.mssv < l.head->info.mssv) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;

	while (q->next!=nullptr && q->next->info.mssv<x.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

//Sap xep danh sach lien ket
int cmpAsc(Node* a, Node* b) {
	return a->info.mssv - b->info.mssv;
}

void sortList(LinkedList l, int func(Node*, Node*)) {
	if (isEmpty(l))
		return;

	for (Node* i = l.head; i ->next != nullptr; i=i->next) {
		for (Node* j = i ->next; j != nullptr; j=j->next) {
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

void nhapDsTuFile(LinkedList& l) {
	//Tao doi tuong nhap/xuat file
	ifstream fin("SinhVien.txt");

	if (fin.is_open()) {
		SinhVien sv;

		while (!fin.eof()) {
			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			fin.getline(sv.queQuan, 100, '#');
			fin >> sv.dtb;

			addTail(l, sv);
		}

		fin.close();
	}
	else
		cout << "Khong tim thay file!\n";
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

	nhapDsTuFile(l);

	printList(l);

	destroyList(l);
	return 0;
}
