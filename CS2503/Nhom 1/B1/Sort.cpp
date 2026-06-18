#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

//Selection Sort
void selectionSort(long a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int pos = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[pos])
				pos = j;
		}
		swap(a[i], a[pos]);
	}
}

//Insertion Sort
void insertionSort(long a[], int n) {
	for (int i = 1; i < n; i++) {
		int x = a[i];
		int j = i - 1;
		while (j >= 0 && x < a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}

void printList(long a[], int n) {
	for (int i = 0; i < 100; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	const int MAX = 100000;

	long a[MAX];
	//TH1
	/*for (int i = 0; i < MAX; i++) {
		a[i] = MAX - i;
	}*/

	//TH2
	for (int i = 0; i < MAX; i++) {
		a[i] = i+1;
	}

	auto start = high_resolution_clock::now();
	insertionSort(a, MAX);
	auto end = high_resolution_clock::now();

	cout << "Time: " << duration_cast<seconds>(end - start).count() << endl;

	printList(a, MAX);

	return 0;
}