#include <iostream>
#include <stack>

using namespace std;

class Node {
    int key;
    int height;
    Node *left;
    Node *right;
public:
    Node();

    int getKey() { return key; }
    int getHeight() { return height; }
    Node *getLeft() { return left; }
    Node *getRight() { return right; }

    bool isNull() {
        if(this == nullptr) {
            return true;
        }
        return false;
    }

    void setHeight(int h) { height = h; }
    void setKey(int k) { key = k; }
    void setLeft(Node *n) { left = n; }
    void setRight(Node *n) { right = n; }
};

Node::Node() {
    key = 0;
    height = 0;
    left = nullptr;
    right = nullptr;
}

class BST {
    Node *root;
    int size;
public:
    BST();
    Node *getRoot() { return root; }
    int getSize() { return size; }
    void setRoot(Node *newNode) { root = newNode; }
    void added() { size++; }
    void deleted() { size--; }
};

BST::BST()  {
    root = nullptr;
    size = 0;
}

stack<Node*> st;

Node *getNode() {
    Node *NewNode = new Node();
    return NewNode;
}

int height(Node *N) {
    return N->getHeight();
}

int noNodes(Node *N) {
    if(N == nullptr) return 0;
    int noNode = 1;
    if(!N->getLeft()->isNull())
        noNode += noNodes(N->getLeft());
    if(!N->getRight()->isNull())
        noNode += noNodes(N->getRight());
    return noNode;
}

Node *minNode(Node *N) {
    while(!N->getLeft()->isNull()) {
        st.push(N);
        N = N->getLeft();
    }
    return N;
}

Node *maxNode(Node *N) {
    while(!N->getRight()->isNull()) {
        st.push(N);
        N = N->getRight();
    }
    return N;
}

void insertBST(BST *T, int newKey) {
    Node *P = T->getRoot();
    Node *Q;

    while(!P->isNull()) {
        if(newKey == P->getKey()) return;

        Q = P;
        st.push(Q);

        if(newKey < P->getKey()) P = P->getLeft();
        else P = P->getRight();
    }

    // getNode 사용
    Node *newNode = getNode();
    newNode->setKey(newKey);

    if(T->getRoot()->isNull()) T->setRoot(newNode);
    else if (newKey < Q->getKey()) Q->setLeft(newNode);
    else Q->setRight(newNode);

    // height 사용
    while(!st.empty()) {
        Q = st.top(); st.pop();
        int maxHeight = 0;
        Node *LEFT = Q->getLeft();
        Node *RIGHT = Q->getRight();
        if(LEFT->isNull())
            maxHeight = height(RIGHT);
        else if(RIGHT->isNull())
            maxHeight = height(LEFT);
        else {
            maxHeight = height(LEFT);
            if(maxHeight < height(RIGHT)) maxHeight = height(RIGHT);
        }
        Q->setHeight(1 + maxHeight);
    }
}

void deleteBST(BST *T, int deleteKey) {
    Node *P = T->getRoot();
    Node *Q = nullptr;

    while(!P->isNull() && deleteKey != P->getKey()) {
        Q = P;
        st.push(Q);

        if(deleteKey < P->getKey()) P = P->getLeft();
        else P = P->getRight();
    }

    if(P->isNull()) return;

    if(!P->getLeft()->isNull() && !P->getRight()->isNull()) {
        st.push(P);
        Node *tempNode = P;

        // height, minNode, maxNode 사용
        if(height(P->getLeft()) < height(P->getRight()))
            P = minNode(P->getRight());
        else if(height(P->getLeft()) > height(P->getRight()))
            P = maxNode(P->getLeft());
        else {
            // noNodes 사용
            if(noNodes(P->getLeft()) <= height(P->getRight()))
                P = minNode(P->getRight());
            else
                P = maxNode(P->getLeft());
        }

        tempNode->setKey(P->getKey());
        Q = st.top();
    }

    if (P->getLeft()->isNull() && P->getRight()->isNull()) {
        if(Q->isNull()) T->setRoot(T->getRoot()->getLeft());
        else if(Q->getLeft() == P) Q->setLeft(P->getRight());
        else Q->setRight(P->getLeft());
    }
    else {
        if (!P->getLeft()->isNull()) {
            if(Q->isNull()) T->setRoot(T->getRoot()->getLeft());
            else if(Q->getLeft() == P) Q->setLeft(P->getLeft());
            else Q->setRight(P->getLeft());
        }
        else {
            if(Q->isNull()) T->setRoot(T->getRoot()->getRight());
            else if(Q->getLeft() == P) Q->setLeft(P->getRight());
            else Q->setRight(P->getRight());
        }
    }

    delete P;

    // height 사용
    while(!st.empty()) {
        Q = st.top(); st.pop();
        int maxHeight = 0;
        if(Q->getLeft()->isNull() && Q->getRight()->isNull())
            maxHeight = 0;
        else if(Q->getLeft()->isNull())
            maxHeight = Q->getRight()->getHeight();
        else if(Q->getRight()->isNull())
            maxHeight = Q->getLeft()->getHeight();
        else {
            maxHeight = Q->getLeft()->getHeight();
            if(maxHeight < Q->getRight()->getHeight()) maxHeight = Q->getRight()->getHeight();
        }
        Q->setHeight(1 + maxHeight);
    }
}

void inOrder(Node *N) {
    if(N == nullptr) return;
    if(!N->getLeft()->isNull())
        inOrder(N->getLeft());
    cout<<N->getKey()<<" ";
    if(!N->getRight()->isNull())
        inOrder(N->getRight());
}

void inOrderBST(BST *T) {
    inOrder(T->getRoot());
    cout<<endl;
}


int main() {
    BST *T = new BST();
    // 삽입
    insertBST(T, 25); inOrderBST(T);
    insertBST(T, 500); inOrderBST(T);
    insertBST(T, 33); inOrderBST(T);
    insertBST(T, 49); inOrderBST(T);
    insertBST(T, 17); inOrderBST(T);
    insertBST(T, 403); inOrderBST(T);
    insertBST(T, 29); inOrderBST(T);
    insertBST(T, 105); inOrderBST(T);
    insertBST(T, 39); inOrderBST(T);
    insertBST(T, 66); inOrderBST(T);
    insertBST(T, 305); inOrderBST(T);
    insertBST(T, 44); inOrderBST(T);
    insertBST(T, 19); inOrderBST(T);
    insertBST(T, 441); inOrderBST(T);
    insertBST(T, 390); inOrderBST(T);
    insertBST(T, 12); inOrderBST(T);
    insertBST(T, 81); inOrderBST(T);
    insertBST(T, 50); inOrderBST(T);
    insertBST(T, 100); inOrderBST(T);
    insertBST(T, 999); inOrderBST(T);

    // 삭제
    deleteBST(T, 25); inOrderBST(T);
    deleteBST(T, 500); inOrderBST(T);
    deleteBST(T, 33); inOrderBST(T);
    deleteBST(T, 49); inOrderBST(T);
    deleteBST(T, 17); inOrderBST(T);
    deleteBST(T, 403); inOrderBST(T);
    deleteBST(T, 29); inOrderBST(T);
    deleteBST(T, 105); inOrderBST(T);
    deleteBST(T, 39); inOrderBST(T);
    deleteBST(T, 66); inOrderBST(T);
    deleteBST(T, 305); inOrderBST(T);
    deleteBST(T, 44); inOrderBST(T);
    deleteBST(T, 19); inOrderBST(T);
    deleteBST(T, 441); inOrderBST(T);
    deleteBST(T, 390); inOrderBST(T);
    deleteBST(T, 12); inOrderBST(T);
    deleteBST(T, 81); inOrderBST(T);
    deleteBST(T, 50); inOrderBST(T);
    deleteBST(T, 100); inOrderBST(T);
    deleteBST(T, 999); inOrderBST(T);

    // 재삽입
    insertBST(T, 25); inOrderBST(T);
    insertBST(T, 500); inOrderBST(T);
    insertBST(T, 33); inOrderBST(T);
    insertBST(T, 49); inOrderBST(T);
    insertBST(T, 17); inOrderBST(T);
    insertBST(T, 403); inOrderBST(T);
    insertBST(T, 29); inOrderBST(T);
    insertBST(T, 105); inOrderBST(T);
    insertBST(T, 39); inOrderBST(T);
    insertBST(T, 66); inOrderBST(T);
    insertBST(T, 305); inOrderBST(T);
    insertBST(T, 44); inOrderBST(T);
    insertBST(T, 19); inOrderBST(T);
    insertBST(T, 441); inOrderBST(T);
    insertBST(T, 390); inOrderBST(T);
    insertBST(T, 12); inOrderBST(T);
    insertBST(T, 81); inOrderBST(T);
    insertBST(T, 50); inOrderBST(T);
    insertBST(T, 100); inOrderBST(T);
    insertBST(T, 999); inOrderBST(T);

    // 삭제2
    deleteBST(T, 999); inOrderBST(T);
    deleteBST(T, 100); inOrderBST(T);
    deleteBST(T, 50); inOrderBST(T);
    deleteBST(T, 81); inOrderBST(T);
    deleteBST(T, 12); inOrderBST(T);
    deleteBST(T, 390); inOrderBST(T);
    deleteBST(T, 441); inOrderBST(T);
    deleteBST(T, 19); inOrderBST(T);
    deleteBST(T, 44); inOrderBST(T);
    deleteBST(T, 305); inOrderBST(T);
    deleteBST(T, 66); inOrderBST(T);
    deleteBST(T, 39); inOrderBST(T);
    deleteBST(T, 105); inOrderBST(T);
    deleteBST(T, 29); inOrderBST(T);
    deleteBST(T, 403); inOrderBST(T);
    deleteBST(T, 17); inOrderBST(T);
    deleteBST(T, 49); inOrderBST(T);
    deleteBST(T, 33); inOrderBST(T);
    deleteBST(T, 500); inOrderBST(T);
    deleteBST(T, 25); inOrderBST(T);
    return 0;
}