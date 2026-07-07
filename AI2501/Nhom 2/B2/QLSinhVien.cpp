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

struct Node
{
	//Vung thong tin
	SinhVien info;
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

void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}
	Node* q = l.head;
	while (q != nullptr) {
		//cout << q->info;
		xuat1Sv(q->info);
		q = q->next;
		if (q)
			cout << "->";
	}
	cout << endl;
}

//Tim kiem
Node* search(LinkedList l, const int key) {
	Node* q = l.head;
	while (q != nullptr) {
		if (q->info.mssv == key)
			return q;
		q = q->next;
	}
	return q;
}


//Them phan tu x vao sau phan tu key
void insertAfter(LinkedList l, SinhVien x, SinhVien key) {
	Node* q = search(l, key.mssv);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(LinkedList& l, SinhVien x) {
	if (isEmpty(l) || x.mssv < l.head->info.mssv) {
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

//Them 1 phan tu x vao phia truoc phan tu key
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
void addTail(LinkedList& l, SinhVien x) {
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

int main() {
	LinkedList l;
	init(l);

	nhapDsTuFile(l);
	printList(l);

	destroyList(l);
	//printList(l);
	return 0;
}