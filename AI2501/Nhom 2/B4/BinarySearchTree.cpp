#include <iostream>
#include <stack>
using namespace std;

struct Node
{
	int key;
	Node* left, * right;
};

struct BST
{
	Node* root;
};

void init(Node*& root) {
	root = nullptr;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->key = x;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}

void insertNodeRec(Node*& root, int x) {
	if (root == nullptr)
		root = createNode(x);
	else if (x < root->key)
		insertNodeRec(root->left, x);
	else if (x > root->key)
		insertNodeRec(root->right, x);
	else
		return;
}

void insertNodeNoRec(Node*& root, const int x) {
	Node* p = createNode(x);
	if (root == NULL) {
		root = p;
		return;
	}
	Node* q = root;
	Node* parent = NULL;

	while (q != NULL) {
		parent = q;
		if (x > q->key)
			q = q->right;
		else if (x < q->key)
			q = q->left;
		else
			return;
	}

	if (x > parent->key)
		parent->right = p;
	else
		parent->left = p;
}

void duyetLNRRec(Node* root) {
	if (root != nullptr) {
		duyetLNRRec(root->left);
		cout << root->key << " ";
		duyetLNRRec(root->right);
	}
}

void duyetLNRNoRec(Node* root) {
	stack<Node*> s;
	Node* p = root;

	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			s.push(p);
			p = p->left;
		}

		p = s.top();
		s.pop();

		cout << p->key << "\t";
		p = p->right;
	}
}

//Duyet LRN, NLR, duyet theo chieu rong

//Kiem tra tinh chat CNPTK

//Thao tac xoa dung de quy

//Thao tac kiem tra rong
bool isEmpty(Node* root) {
	return root == NULL;
}

//Thao tac xoa
void delNodeNoRec(Node*& root, int key) {
	Node* q = root;
	Node* parent = NULL;

	//Tim node q chua key can xoa
	while (q != NULL && q->key != key) {
		parent = q;
		if (key > q->key)
			q = q->right;
		else
			q = q->left;
	}

	//Khong tim thay
	if (q == NULL)
		return;

	//q la nut bac 1 hoac nut la
	if (q->left == NULL || q->right == NULL) {
		Node* temp = q->left != NULL ? q->left : q->right;

		if (q == root)
			root = temp;
		else if (key > parent->key)
			parent->right = temp;
		else
			parent->left = temp;

		delete q;
		return;
	}

	//q la nut bac 2
	Node* temp = q->left;
	parent = NULL;
	while (temp->right != NULL) {
		parent = temp;
		temp = temp->right;
	}

	//Chep du lieu cua temp cho q
	q->key = temp->key;
	if (parent != NULL)
		parent->right = temp->left;
	else
		q->left = temp->left;

	temp->left = NULL;
	delete temp;
}

//Thao tac tim kiem
Node* search(Node* root, int key) {
	Node* q = root;
	while (q != NULL && q->key != key) {
		if (key > q->key)
			q = q->right;
		else
			q = q->left;
	}

	return q;
}

//Giai phong
void detroyTree(Node*& root) {
	while (!isEmpty(root)) {
		delNodeNoRec(root, root->key);
	}
}

int main() {
	BST t;
	init(t.root);

	insertNodeRec(t.root, 40);
	insertNodeRec(t.root, 30);
	insertNodeRec(t.root, 10);
	insertNodeRec(t.root, 60);
	insertNodeRec(t.root, 25);

	duyetLNRRec(t.root);
	detroyTree(t.root);
	return 0;
}