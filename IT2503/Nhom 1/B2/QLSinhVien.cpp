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


struct Node {
	//Vung thong tin
	SinhVien info;

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

//Them cuoi danh sach
void addTail(LinkedList& l, SinhVien x) {
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

//Them phan tu vao truoc phan tu mang gia tri key
void insertBefore(LinkedList& l, SinhVien x, int key) {
	if (isEmpty(l))
		return;

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
	if (prev == nullptr) {
		l.head = p;
	}
	else {
		prev->next = p;
	}
}

//Thao tac tim kiem phan tu key trong danh
Node* search(LinkedList l, SinhVien key) {
	Node* p = l.head;
	while (p != nullptr) {
		if (p->info.mssv == key.mssv)
			return p;
		p = p->next;
	}
	return p;
}

//Thao tac them vao sau phan tu key 1 gia tri x
void insertAfter(LinkedList l, SinhVien x, SinhVien key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

//Sap xep danh sach
int cmpAsc(Node* a, Node* b) {
	return a->info.mssv - b->info.mssv;
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
void insertOrdered(LinkedList& l, SinhVien x) {
	if (isEmpty(l) || l.head->info.mssv > x.mssv) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;
	while (q->next != nullptr && q->info.mssv < x.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
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

//Duyet danh sach lien ket va in ra man hinh
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

void printList(LinkedList l) {
	if (l.head == nullptr) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = l.head;
	while (p != nullptr) {
		xuat1Sv(p->info);
		//cout << p->info << " ";
		p = p->next;
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

	nhapDsTuFile(l);

	printList(l);

	destroyList(l);
	//printList(l);
	return 0;
}