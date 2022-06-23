#include <iostream>
using namespace std;

struct Node{
    int ID;
    Node* prev;
    Node* next;
};

Node* createNode(int id, Node* nodes);
Node* insert(Node* pos, Node* node, int offset);
void printList(Node* node, int length);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    Node* nodes = new Node[n];
    Node* cur = nullptr;
    Node* node = nullptr;
    int id = 0;
    for(int i = 0; i < n; i++){
        cin >> id;
        node = createNode(id, nodes);
        cur = insert(cur, node, m);
    }
    printList(cur, n);
    delete [] nodes;
    return 0;
}

Node* createNode(int id, Node* nodes){
    static int cnt = 0;
    Node* node = &nodes[cnt++];
    node->ID = id;
    return node;
}

Node* insert(Node* cur, Node* node, int offset){
    if(node == nullptr) return nullptr;
    if(cur == nullptr){
        cur = node;
        cur->prev = node;
        cur->next = node;
    }
    else{
        for(int i = 0; i < offset; i++)
            cur = cur->next;
        Node* p = cur->prev;
        cur->prev = node;
        node->next = cur;
        node->prev = p;
        p->next = node;
    }
    return node;
}

void printList(Node* node, int length){
    if(node == nullptr) return;
    for(int i = 0; i < length; i++){
        cout << node->ID << " ";
        node = node->prev;
    }
}