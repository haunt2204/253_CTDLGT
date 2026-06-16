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

void nhap1Sv(SinhVien &sv){
	cout << "Nhap MSSV: ";
	cin >> sv.mssv;
	cin.ignore();
	cout << "Nhap ho ten: ";
	getline(cin, sv.hoTen, '\n');
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cout << "Nhap que quan: ";
	cin>> sv.queQuan;
	cout << "Nhap diem TB: ";
	cin >> sv.dtb;
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

//Danh sach sinh vien
struct DSSV {
	SinhVien* ds;
	int siSo;
};

//Khoi tao rong
void init(DSSV& l) {
	l.ds = NULL;
	l.siSo = 0;
}

//Nhap DSSV
void inputDsSv(DSSV& l) {
	do {
		cout << "Nhap si so: ";
		cin >> l.siSo;
	} while (l.siSo <= 0);

	l.ds = new SinhVien[l.siSo];

	for (int i = 0; i < l.siSo; i++) {
		nhap1Sv(l.ds[i]);
	}
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

//Nhap danh sach tu file
void inputFromFile(DSSV& l) {
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

			pushBackArr(l.ds, l.siSo, sv);
		}

		fin.close();
	}
}

//Xuat danh sach ra man hinh
void printList(DSSV l) {
	if (l.ds == 0) {
		cout << "DS rong!\n";
		return;
	}

	for (int i = 0; i < l.siSo; i++) {
		xuat1Sv(l.ds[i]);
	}
}

//Giai phong vung nho
void detroyList(DSSV& l) {
	delete[]l.ds;
	l.ds = NULL;
	l.siSo = 0;
}

//Tim kiem
int linearSearh(DSSV l, const int id) {
	for (int i = 0; i < l.siSo; i++) {
		if (l.ds[i].mssv == id)
			return i;
	}

	return -1;
}

int binarySearch(DSSV l, const int id) {
	int left = 0, right = l.siSo;

	while (left < right) {
		int mid = (left + right) / 2;

		if (l.ds[mid].mssv == id)
			return mid;

		if (l.ds[mid].mssv > id)
			right = mid;
		else
			left = mid + 1;
	}

	return -1;
}

//Sap xep danh sach: mssv, hoTen, diemTb,...
int cmpWithId(SinhVien sv1, SinhVien sv2) {
	return sv1.mssv - sv2.mssv;
}

int cmpWithIdDesc(SinhVien sv1, SinhVien sv2) {
	return -(sv1.mssv - sv2.mssv);
}

int cmpWithAdr(SinhVien sv1, SinhVien sv2) {
	return strcmp(sv1.queQuan, sv2.queQuan);
}

int cmpWithAvr(SinhVien sv1, SinhVien sv2) {
	return sv1.dtb - sv2.dtb;
}

void sortArr(DSSV &l, int func(SinhVien, SinhVien)=cmpWithId) {
	for (int i = 0; i < l.siSo - 1; i++) {
		for (int j = i + 1; j < l.siSo; j++) {
			if (func(l.ds[j], l.ds[i]) < 0)
				swap(l.ds[i], l.ds[j]);
		}
	}
}

int main() {
	DSSV l;

	init(l);
	/*inputDsSv(l);

	printList(l);*/

	inputFromFile(l);
	printList(l);

	int pos = binarySearch(l, 2018010);

	cout << "===================TIM KIEM=============\n";
	if (pos != -1)
		xuat1Sv(l.ds[pos]);
	/*cout << l.ds[pos] << endl;*/
	else
		cout << "Khong tim thay!\n";


	cout << "===================SAP XEP=============\n";
	sortArr(l);
	printList(l);

	detroyList(l);
	return 0;
}