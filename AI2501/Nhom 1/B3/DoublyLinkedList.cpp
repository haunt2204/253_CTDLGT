#include <iostream>
using namespace std;

struct Node
{
    int info;
    Node* next, * prev;
};

struct DoublyLinkedList
{
    Node* head, * tail;
};

//Khoi tao rong
void init(DoublyLinkedList &l) {
    l.head = nullptr;
    l.tail = nullptr;
}

//Tao node moi
Node* createNode(int x) {
    Node* p = new Node;
    p->info = x;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

//Them phan tu vao dau danh sach
void addHead(DoublyLinkedList& l, int x) {
    Node* p = createNode(x);

    if (l.head == nullptr) {
        l.tail = p;
    }
    else {
        p->next = l.head;
        l.head->prev = p;
    }

    l.head = p;
}
//Them phan tu vao cuoi danh sach
void addTail(DoublyLinkedList& l, int x) {
    Node* p = createNode(x);

    if (l.tail == nullptr) {
        l.head = p;
    }
    else {
        p->prev = l.tail;
        l.tail->next = p;
    }

    l.tail = p;
}
//Duyet danh sach: tu dau, tu cuoi
void printListFromHead(DoublyLinkedList l) {
    if (l.head == nullptr) {
        cout << "Danh sach rong!\n";
        return;
    }

    Node* p = l.head;
    while (p != nullptr) {
        cout << p->info << " ";
        p = p->next;
    }

    cout << endl;
}

void printListFromTail(DoublyLinkedList l) {
    if (l.head == nullptr) {
        cout << "Danh sach rong!\n";
        return;
    }

    Node* p = l.tail;
    while (p != nullptr) {
        cout << p->info << " ";
        p = p->prev;
    }
    cout << endl;
}

//Thao tac tim kiem: phan tu q mang gia tri key, min, max
Node* search(DoublyLinkedList l, int key) {
    Node* p = l.head;
    while (p != nullptr) {
        if (p->info == key)
            return p;
        p = p->next;
    }
    return nullptr;
}

bool max(int a, int b) {
    return a > b;
}

bool min(int a, int b) {
    return a < b;
}

Node* findMax(DoublyLinkedList l, bool func(int, int)=min) {
    if (l.head == nullptr)
        return nullptr;

    Node* res = l.head;
    Node* q = l.head->next;

    while (q != nullptr) {
        if (func(q->info, res->info))
            res = q;
        q = q->next;
    }

    return res;
}

//Them phan tu x vao sau phan tu mang gia tri key
void insertAfter(DoublyLinkedList l, int x, int key) {
    Node* q = search(l, key);

    if (q == nullptr)
        return;

    if (q == l.tail) {
        addTail(l, x);
        return;
    }

    Node* p = createNode(x);
    Node* qNext = q->next;

    p->next = qNext;
    qNext->prev = p;

    p->prev = q;
    q->next = p;
}

//Xoa phan tu cuoi danh sach
void delHead(DoublyLinkedList& l) {
    if (l.head == nullptr)
        return;
    
    Node* p = l.head;
    l.head = l.head->next;

    if(l.head!=nullptr)
        l.head->prev = nullptr;
    else {
        l.tail = nullptr;
    }

    p->next = nullptr;
    delete p;
}


//Giai phong vung nho
void destroyList(DoublyLinkedList& l) {
    while (l.head != nullptr) {
        delHead(l);
    }
}

int main()
{
    DoublyLinkedList l;
    init(l);

    addHead(l, 6);
    addHead(l, 4);
    addHead(l, 2);

    addTail(l, 999);

    printListFromHead(l);

    cout << "==============THEM SAU================\n";
    insertAfter(l, 9, 999);
    printListFromHead(l);

    cout << "==============TIM CUC TRI================\n";
    cout << "Max: " << findMax(l, max)->info << endl;

    destroyList(l);
    printListFromTail(l);
    return 0;
}