#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SinhVien {
	int mssv;
	string hoTen = "";
	char ngaySinh[11] = "";
	char queQuan[100] = "";
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

//Thao tac khoi tao rong
void init(LinkedList& l) {
	l.head = nullptr;
}

bool isEmpty(LinkedList l) {
	return l.head == nullptr;
}

//Thao tac them phan tu vao dau danh sach
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

//Thao tac duyet danh sach
void printList(LinkedList l) {
	if (isEmpty(l)) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* p = l.head;
	while (p != nullptr) {
		xuat1Sv(p->info);
		/*cout << p->info << " ";*/
		p = p->next;
	}

	cout << endl;
}

//Tim kiem phan tu mang gia tri key
Node* search(LinkedList l, int key) {
	Node* p = l.head;
	while (p != nullptr) {
		if (p->info.mssv == key)
			return p;
		p = p->next;
	}
	return p;
}

//Them phan tu x vao danh sach phia sau phan tu mang gia tri key
void insertAfter(LinkedList l, SinhVien x, int key) {
	Node* q = search(l, key);
	if (q != nullptr) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
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
void insertBefore(LinkedList& l, SinhVien x, int key) {
	Node* q = l.head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.mssv != key) {
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
void insertOrdered(LinkedList& l, SinhVien x) {
	if (isEmpty(l) || x.mssv < l.head->info.mssv) {
		addHead(l, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = l.head;
	while (q->next != nullptr && x.mssv > q->next->info.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

void nhapDsTuFile(LinkedList& l) {
	//Tao doi tuong nhap/xuat file
	ifstream fin("SinhVien.txt");//Duong dan tuong doi

	if (fin.is_open()) {
		//Thao tac

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

//Thao tac sap xep danh sach lien ket
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

	nhapDsTuFile(l);

	printList(l);

	destroyList(l);
	/*printList(l);*/
	return 0;
}