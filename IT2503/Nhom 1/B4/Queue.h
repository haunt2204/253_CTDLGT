#include <iostream>
using namespace std;

struct Node
{
	char* info;
	Node* next;
};

struct Queue
{
	Node* head, * tail;
};

//Khoi tao rong
void init(Queue& q) {
	q.head = q.tail = nullptr;
}

//Kiem tra rong
bool isEmpty(Queue q) {
	return q.head == nullptr;
}

//Them vao hang doi
Node* createNode(char* x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	return p;
}

void enQueue(Queue& q, char* x) {
	Node* p = createNode(x);
	if (isEmpty(q)) {
		q.head = q.tail = p;
		return;
	}

	q.tail->next = p;
	q.tail = p;
}
//Lay ra tu hang doi
char* deQueue(Queue& q) {
	if (!isEmpty(q)) {
		Node* p = q.head;
		char* data = p->info;

		q.head = q.head->next;
		if (q.head == nullptr)
			q.tail = nullptr;

		p->next = nullptr;
		delete p;
		return data;
	}
	return nullptr;
}
