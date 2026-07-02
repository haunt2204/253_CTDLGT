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
Node* createNode(SinhVien x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}

void addHead(LinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	p->next = l.head;
	l.head = p;
}

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


//Duyet danh sach xuat ra man hinh
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;

	while (p != nullptr) {
		//cout << p->info << " ";
		xuat1Sv(p->info);
		p = p->next;
	}

	cout << endl;
}
//Tim 1 phan tu trong danh sach
Node* search(LinkedList l, const int key) {
	Node* p = l.head;

	while (p != nullptr) {
		if (p->info.mssv == key)
			return p;
		p = p->next;
	}

	return nullptr;
}

void insertAfter(LinkedList l, const SinhVien x, const int key) {
	Node* q = search(l, key);

	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertBefore(LinkedList& l, const SinhVien x, const int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.mssv != key) {
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

//Them vao danh sach da co thu tu
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

			addHead(l, sv);
		}

		fin.close();
	}
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
	return a->info.mssv - b->info.mssv;
}

void sortList(LinkedList l, int func(Node*, Node*) = cmpAsc) {
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

	inputFromFile(l);

	printList(l);
	destroyList(l);
	return 0;
}