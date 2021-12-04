#include <iostream>
#include <string>
#include <stack>

using namespace std;

string rotationType;

class NODE {
    int key;
    int height;
    int bf;
    NODE *left;
    NODE *right;
public:
    NODE();

    int getKey() { return key; }
    int getHeight() {
        if(this == nullptr)
            return 0;
        return height;
    }
    int getBF() {
        if(this == nullptr)
            return 0;
        return bf;
    }
    NODE *getLeft() {
        if(this == nullptr)
            return nullptr;
        return left;
    }
    NODE *getRight() {
        if(this == nullptr)
            return nullptr;
        return right;
    }

    void setKey(int k) { key = k; }
    void setHeight(int h) {height = h; }
    void setBF(int b) { bf = b; }
    void setLeft(NODE *n) { left = n; }
    void setRight(NODE *n) { right = n; }

    bool isNull() {
        if(this == nullptr)
            return true;
        return false;
    }
};

NODE::NODE() {
    key = 0;
    height = 1;
    bf = 0;
    left = nullptr;
    right = nullptr;
}

class AVL {
    NODE *root;
    int size;
public:
    AVL();

    NODE *getRoot() { return root; }
    int getSize() { return size; }

    void setRoot(NODE *N) { root = N; }
    void setSize(int s) { size = s; }
};

AVL::AVL() {
    root = nullptr;
    size = 0;
}

int maxHeight(int a, int b) {
    return a>b?a:b;
}

void rotateTree(AVL *T, NODE *X, NODE *F) {
    if(rotationType == "LL") {
        NODE *TempNode = X->getLeft();
        if(F->isNull()) {
            T->setRoot(TempNode);
        }
        else if(F->getLeft() == X) {
            F->setLeft(TempNode);
        }
        else {
            F->setRight(TempNode);
        }
        X->setLeft(TempNode->getRight());
        TempNode->setRight(X);
        X->setHeight(1 + maxHeight(X->getLeft()->getHeight(), X->getRight()->getHeight()));
        X->setBF(X->getLeft()->getHeight() - X->getRight()->getHeight());
        TempNode->setHeight(1 + maxHeight(TempNode->getLeft()->getHeight(), TempNode->getRight()->getHeight()));
        TempNode->setBF(TempNode->getLeft()->getHeight() - TempNode->getRight()->getHeight());
        if(F->isNull()) {
            T->getRoot()->setHeight(1 + maxHeight(T->getRoot()->getLeft()->getHeight(), T->getRoot()->getRight()->getHeight()));
            T->getRoot()->setBF(T->getRoot()->getLeft()->getHeight() - T->getRoot()->getRight()->getHeight());
        }
        else {
            F->setHeight(1 + maxHeight(F->getLeft()->getHeight(), F->getRight()->getHeight()));
            F->setBF(F->getLeft()->getHeight() - F->getRight()->getHeight());
        }
    }
    else if(rotationType == "LR") {
        NODE *TempNode1 = X->getLeft();
        NODE *TempNode2 = TempNode1->getRight();
        if(F->isNull()) {
            T->setRoot(TempNode2);
        }
        else if(F->getLeft() == X) {
            F->setLeft(TempNode2);
        }
        else {
            F->setRight(TempNode2);
        }
        TempNode1->setRight(TempNode2->getLeft());
        X->setLeft(TempNode2->getRight());
        TempNode2->setLeft(TempNode1);
        TempNode2->setRight(X);
        X->setHeight(1 + maxHeight(X->getLeft()->getHeight(), X->getRight()->getHeight()));
        X->setBF(X->getLeft()->getHeight() - X->getRight()->getHeight());
        TempNode1->setHeight(1 + maxHeight(TempNode1->getLeft()->getHeight(), TempNode1->getRight()->getHeight()));
        TempNode1->setBF(TempNode1->getLeft()->getHeight() - TempNode1->getRight()->getHeight());
        TempNode2->setHeight(1 + maxHeight(TempNode2->getLeft()->getHeight(), TempNode2->getRight()->getHeight()));
        TempNode2->setBF(TempNode2->getLeft()->getHeight() - TempNode2->getRight()->getHeight());
        if(F->isNull()) {
            T->getRoot()->setHeight(1 + maxHeight(T->getRoot()->getLeft()->getHeight(), T->getRoot()->getRight()->getHeight()));
            T->getRoot()->setBF(T->getRoot()->getLeft()->getHeight() - T->getRoot()->getRight()->getHeight());
        }
        else {
            F->setHeight(1 + maxHeight(F->getLeft()->getHeight(), F->getRight()->getHeight()));
            F->setBF(F->getLeft()->getHeight() - F->getRight()->getHeight());
        }
    }
    else if(rotationType == "RR") {
        NODE *TempNode = X->getRight();
        if(F->isNull()) {
            T->setRoot(TempNode);
        }
        else if(F->getLeft() == X) {
            F->setLeft(TempNode);
        }
        else {
            F->setRight(TempNode);
        }
        X->setRight(TempNode->getLeft());
        TempNode->setLeft(X);
        X->setHeight(1 + maxHeight(X->getLeft()->getHeight(), X->getRight()->getHeight()));
        X->setBF(X->getLeft()->getHeight() - X->getRight()->getHeight());
        TempNode->setHeight(1 + maxHeight(TempNode->getLeft()->getHeight(), TempNode->getRight()->getHeight()));
        TempNode->setBF(TempNode->getLeft()->getHeight() - TempNode->getRight()->getHeight());
        if(F->isNull()) {
            T->getRoot()->setHeight(1 + maxHeight(T->getRoot()->getLeft()->getHeight(), T->getRoot()->getRight()->getHeight()));
            T->getRoot()->setBF(T->getRoot()->getLeft()->getHeight() - T->getRoot()->getRight()->getHeight());
        }
        else {
            F->setHeight(1 + maxHeight(F->getLeft()->getHeight(), F->getRight()->getHeight()));
            F->setBF(F->getLeft()->getHeight() - F->getRight()->getHeight());
        }
    }
    else if(rotationType == "RL") {
        NODE *TempNode1 = X->getRight();
        NODE *TempNode2 = TempNode1->getLeft();
        if(F->isNull()) {
            T->setRoot(TempNode2);
        }
        else if(F->getLeft() == X) {
            F->setLeft(TempNode2);
        }
        else {
            F->setRight(TempNode2);
        }
        TempNode1->setLeft(TempNode2->getRight());
        X->setRight(TempNode2->getLeft());
        TempNode2->setRight(TempNode1);
        TempNode2->setLeft(X);
        X->setHeight(1 + maxHeight(X->getLeft()->getHeight(), X->getRight()->getHeight()));
        X->setBF(X->getLeft()->getHeight() - X->getRight()->getHeight());
        TempNode1->setHeight(1 + maxHeight(TempNode1->getLeft()->getHeight(), TempNode1->getRight()->getHeight()));
        TempNode1->setBF(TempNode1->getLeft()->getHeight() - TempNode1->getRight()->getHeight());
        TempNode2->setHeight(1 + maxHeight(TempNode2->getLeft()->getHeight(), TempNode2->getRight()->getHeight()));
        TempNode2->setBF(TempNode2->getLeft()->getHeight() - TempNode2->getRight()->getHeight());
        if(F->isNull()) {
            T->getRoot()->setHeight(1 + maxHeight(T->getRoot()->getLeft()->getHeight(), T->getRoot()->getRight()->getHeight()));
            T->getRoot()->setBF(T->getRoot()->getLeft()->getHeight() - T->getRoot()->getRight()->getHeight());
        }
        else {
            F->setHeight(1 + maxHeight(F->getLeft()->getHeight(), F->getRight()->getHeight()));
            F->setBF(F->getLeft()->getHeight() - F->getRight()->getHeight());
        }
    }
}

string checkBalance(AVL *T, int newKey, NODE *P, NODE *Q, NODE* &X, NODE* &F) {
    stack<NODE*> st;

    while(!P->isNull()) {
        if(newKey == P->getKey()) return "NO";

        Q = P;
        st.push(P);

        if(newKey < P->getKey()) P = P->getLeft();
        else P = P->getRight();
    }

    NODE *Y = new NODE();
    Y->setKey(newKey);

    if(T->getRoot()->isNull()) T->setRoot(Y);
    else if(newKey < Q->getKey()) Q->setLeft(Y);
    else Q->setRight(Y);

    while(!st.empty()) {
        Q = st.top(); st.pop();
        Q->setHeight(1 + maxHeight(Q->getLeft()->getHeight(), Q->getRight()->getHeight()));
        Q->setBF(Q->getLeft()->getHeight() - Q->getRight()->getHeight());

        if(Q->getBF() < -1 || 1 < Q->getBF()) {
            if(X->isNull()) {
                X = Q;
                if(st.empty())
                    F = nullptr;
                else
                    F = st.top();
            }
        }
    }

    if(X->isNull()) return "NO";

    if(1 < X->getBF()) {
        if(X->getLeft()->getBF() < 0) {
            return "LR";
        }
        else {
            return "LL";
        }
    }
    else {
        if(X->getRight()->getBF() > 0) {
            return "RL";
        }
        else {
            return "RR";
        }
    }
}

void insertAVL(AVL *T, int newKey) {
    rotationType = "NO";
    NODE *P = T->getRoot();
    NODE *Q = nullptr;
    NODE *X = nullptr;
    NODE *F = nullptr;

    rotationType = checkBalance(T, newKey, P, Q, X, F);

    rotateTree(T, X, F);
}

void deleteAVL(AVL *T, int deleteKey) {
    rotationType = "NO";
    NODE *P = T->getRoot();
    NODE *Q = nullptr;
    NODE *X = nullptr;
    NODE *F = nullptr;
    stack<NODE*> st;

    while(!P->isNull() && deleteKey != P->getKey()) {
        Q = P;
        st.push(P);

        if(deleteKey < P->getKey()) P = P->getLeft();
        else P = P->getRight();
    }

    if(P->isNull()) return;

    if(!P->getLeft()->isNull() && !P->getRight()->isNull()) {
        st.push(P);
        NODE *tempNode = P;

        if(P->getLeft()->getHeight() <= P->getRight()->getHeight()) {
            P = P->getRight();
            while(!P->getLeft()->isNull()) {
                st.push(P);
                P = P->getLeft();
            }
        }
        else {
            P = P->getLeft();
            while(!P->getRight()->isNull()) {
                st.push(P);
                P = P->getRight();
            }
        }

        tempNode->setKey(P->getKey());
        Q = st.top();
    }

    if(P->getLeft()->isNull() && P->getRight()->isNull()) {
        if(Q->isNull()) T->setRoot(nullptr);
        else if(Q->getLeft() == P) Q->setLeft(nullptr);
        else Q->setRight(nullptr);
    }
    else {
        if(!P->getLeft()->isNull()) {
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

    while(!st.empty()) {
        Q = st.top(); st.pop();
        Q->setHeight(1 + maxHeight(Q->getLeft()->getHeight(), Q->getRight()->getHeight()));
        Q->setBF(Q->getLeft()->getHeight() - Q->getRight()->getHeight());

        if(Q->getBF() < -1 || 1 < Q->getBF()) {
            if(X->isNull()) {
                X = Q;
                if(st.empty())
                    F = nullptr;
                else
                    F = st.top();
            }
        }
    }

    if(X->isNull()) return;

    if(1<X->getBF()) {
        if(X->getLeft()->getBF() < 0) {
            rotationType = "LR";
            rotateTree(T, X, F);
        }
        else {
            rotationType = "LL";
            rotateTree(T, X, F);
        }
    }
    else {
        if(X->getRight()->getBF() > 0) {
            rotationType = "RL";
            rotateTree(T, X, F);
        }
        else {
            rotationType = "RR";
            rotateTree(T, X, F);
        }
    }
}

void inorder(NODE *N) {
    if(N->isNull()) return;
    if(!N->getLeft()->isNull()) {
        inorder(N->getLeft());
    }
    cout<<N->getKey()<<" ";
    if(!N->getRight()->isNull()) {
        inorder(N->getRight());
    }
}

void inorderBST(AVL *T) {
    inorder(T->getRoot());
    cout<<endl;
}

int main() {
    AVL *T = new AVL();
    // 삽입
    insertAVL(T, 40); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 11); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 77); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 33); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 20); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 90); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 99); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 70); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 88); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 80); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 66); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 10); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 22); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 30); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 44); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 55); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 50); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 60); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 25); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 49); cout<<rotationType<<endl; inorderBST(T);

    // 삭제 1
    deleteAVL(T, 40); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 11); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 77); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 33); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 20); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 90); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 99); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 70); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 88); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 80); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 66); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 10); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 22); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 30); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 44); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 55); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 50); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 60); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 25); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 49); cout<<rotationType<<endl; inorderBST(T);

    // 재삽입
    insertAVL(T, 40); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 11); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 77); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 33); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 20); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 90); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 99); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 70); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 88); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 80); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 66); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 10); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 22); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 30); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 44); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 55); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 50); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 60); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 25); cout<<rotationType<<endl; inorderBST(T);
    insertAVL(T, 49); cout<<rotationType<<endl; inorderBST(T);

    // 삭제 2
    deleteAVL(T, 49); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 25); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 60); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 50); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 55); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 44); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 30); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 22); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 10); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 66); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 80); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 88); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 70); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 99); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 90); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 20); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 33); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 77); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 11); cout<<rotationType<<endl; inorderBST(T);
    deleteAVL(T, 40); cout<<rotationType<<endl; inorderBST(T);

    return 0;
}