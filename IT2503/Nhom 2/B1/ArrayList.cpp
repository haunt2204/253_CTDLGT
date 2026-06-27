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

//Nhap 1 sinh vien
void nhap1Sv(SinhVien& sv) {
	cout << "Nhap MSSV: ";
	cin >> sv.mssv;
	cin.ignore();
	cout << "Nhap ho ten: ";
	getline(cin, sv.hoTen, '\n');
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cin.ignore();
	cout << "Nhap que quan: ";
	cin.getline(sv.queQuan, 100, '\n');
	cout << "Nhap diem TB: ";
	cin >> sv.dtb;
}

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

//Danh sach sinh vien
struct ArrayList {
	SinhVien* ds;
	int siSo;
};

//Khoi tao rong
void init(ArrayList& l) {
	l.ds = NULL;
	l.siSo = 0;
}

//Nhap danh sach SV
void nhapDsSv(ArrayList& l) {
	do {
		cout << "Nhap si so: ";
		cin >> l.siSo;
	} while (l.siSo<=0);

	//Xin cap phat vung
	l.ds = new SinhVien[l.siSo];

	for (int i = 0; i < l.siSo; i++)
		nhap1Sv(l.ds[i]);
}

//Them phan tu moi vao mang (noi dan kich thuoc)
void pushBackArr(SinhVien*& a, int& n, SinhVien x) {
	n = (a == NULL) ? 1 : n + 1;

	SinhVien* newArr = new SinhVien[n];

	//Chuyen du lieu tu mang a sang newArr
	for (int i = 0; i < n - 1; i++) {
		*(newArr + i) = *(a + i);
	}

	newArr[n - 1] = x;

	delete[]a;
	a = newArr;
}

void nhapDsTuFile(ArrayList& l) {
	//Tao doi tuong nhap/xuat file
	ifstream fin("SinhVien.txt");

	//2018001#Nguyen Van An#15/01/2000#Ha Noi#8.2

	if (fin.is_open()) {
		SinhVien sv;

		while (!fin.eof()) {
			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			fin.getline(sv.queQuan, 100, '#');
			fin >> sv.dtb;

			pushBackArr(l.ds, l.siSo, sv);
		}

		fin.close();
	}
	else
		cout << "Khong tim thay file!\n";
}

//Tim kiem SV theo ID:
int linearSearch(ArrayList l, int id) {
	for (int i = 0; i < l.siSo; i++) {
		if (l.ds[i].mssv == id)
			return i;
	}
	return -1;
}

int binarySearch(ArrayList l, int id) {
	int left = 0, right = l.siSo;

	while (left < right) {
		int mid = (left + right) / 2;

		if (l.ds[mid].mssv == id)
			return mid;

		if (id > l.ds[mid].mssv) {
			left = mid + 1;
		}
		else
			right = mid;
	}
	return -1;
}
//Sap xep danh sach: id, ho ten, diem trung binh,...
int cmpWithId(SinhVien a, SinhVien b) {
	return a.mssv - b.mssv;
}

int cmpWithIdDesc(SinhVien a, SinhVien b) {
	return -(a.mssv - b.mssv);
}

int cmpWithName(SinhVien a, SinhVien b) {
	return a.hoTen.compare(b.hoTen);
}

void sortList(ArrayList& l, int func(SinhVien, SinhVien)) {
	for (int i = 0; i < l.siSo - 1; i++) {
		for (int j = i + 1; j < l.siSo; j++) {
			if (func(l.ds[j], l.ds[i])<0) {
				swap(l.ds[i], l.ds[j]);
			}
		}
	}
}

//Xuat danh sach SV
void xuatDsSv(ArrayList l) {
	if (l.ds == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	for (int i = 0; i < l.siSo; i++)
		xuat1Sv(l.ds[i]);
}

//Giai phong vung nho
void destroyList(ArrayList& l) {
	delete[]l.ds;
	init(l);
}

int main() {
	ArrayList l;
	init(l);
	nhapDsTuFile(l);
	//nhapDsSv(l);
	xuatDsSv(l);

	cout << "==============TIM KIEM============\n";
	int pos = binarySearch(l, 2018004);
	if (pos != -1) {
		xuat1Sv(l.ds[pos]);
	}
	else
		cout << "Khong tim thay!\n";

	cout << "===================SAP XEP===============\n";
	sortList(l, [](SinhVien a, SinhVien b) {return strcmp(a.queQuan, b.queQuan); });
	xuatDsSv(l);

	destroyList(l);
	return 0;
}