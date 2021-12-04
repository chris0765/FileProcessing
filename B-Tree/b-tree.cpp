#include <iostream>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

class NODE {
    int m;
    int n;
    vector<int> K;
    vector<NODE*> P;
    vector<int*> A;
public:
    NODE() {
        m = 0;
        n = 0;
    }
    NODE(int M) {
        m = M;
        n = 0;
        K.resize(M-1, 0);
        P.resize(M, nullptr);
        if(P.size() == 2) {
            cout<<"check"<<endl;
        }
        A.resize(M-1, nullptr);
    }

    int getN() { return n; }
    int getM() { return m; }
    int getPSize() { return P.size(); }
    vector<int> getK() { return K; }
    int getK(int idx) { return K[idx]; }
    void setK(int idx, int key) {
        K[idx] = key;
    }
    void insertK(int newKey) {
        for(int i=0; i<n; i++) {
            if(K[i]>newKey) {
                K.insert(K.begin() + i, newKey);
                n++;
                K.pop_back();
                return;
            }
        }
        K[n] = newKey;
        n++;
    }
    void deleteK(int idx) {
        K.erase(K.begin() + idx);
        K.push_back(0);
        n--;
    }
    vector<NODE*> getP() { return P; }
    NODE* getP(int idx) {
        return P[idx];
    }
    void insertP(NODE* newNode) {
        if(newNode->isNull()) return;
        for(int i=0; i<n; i++) {
            if(K[i]>newNode->getK(0)) {
                P.insert(P.begin() + i, newNode);
                P.pop_back();
                return;
            }
        }
        P[n] = newNode;
    }
    void deleteP(int idx) {
        P.erase(P.begin() + idx);
        P.push_back(nullptr);
    }
    vector<int*> getA() { return A; }
    int* getA(int idx) { return A[idx]; }

    void copyNode(NODE* toCopy) {
        n = toCopy->getN();
        for(int i=0; i<n; i++) {
            K[i] = toCopy->getK(i);
            A[i] = toCopy->getA(i);
        }
        for(int i=0; i<=n; i++) {
            P[i] = toCopy->getP(i);
        }
    }
    void copyNodeFirst(NODE* toCopy) {
        K.clear();
        K.assign(m-1, 0);
        A.clear();
        A.assign(m-1, nullptr);
        P.clear();
        P.assign(m, nullptr);
        n = toCopy->getN()/2;
        for(int i=0; i<n; i++) {
            K[i] = toCopy->getK(i);
            A[i] = toCopy->getA(i);
            P[i] = toCopy->getP(i);
        }
        P[n] = toCopy->getP(n);
    }
    void copyNodeSecond(NODE* toCopy) {
        K.clear();
        K.assign(m-1, 0);
        A.clear();
        A.assign(m-1, nullptr);
        P.clear();
        P.assign(m, nullptr);
        n = toCopy->getN()/2;
        for(int i=0; i<n; i++) {
            K[i] = toCopy->getK(i + n + 1);
            A[i] = toCopy->getA(i + n + 1);
            P[i] = toCopy->getP(i + n + 1);
        }
        P[n] = toCopy->getP(toCopy->getN());
    }
    NODE* bestSibling(int idx, int& LorR) {
        int ln = -1;
        int rn = -1;
        if(idx>0) ln = P[idx-1]->getN();
        if(idx<n) rn = P[idx+1]->getN();
        if(ln==-1 && rn == -1) {
            LorR = -1;
            return nullptr;
        }
        else if(ln == -1) {
            LorR = 0;
            return P[idx+1];
        }
        else if(rn == -1) {
            LorR = 1;
            return P[idx-1];
        }
        else if(ln>=rn) {
            LorR = 1;
            return P[idx-1];
        }
        else {
            LorR = 0;
            return P[idx+1];
        }
    }

    bool isNull() {
        if(this == nullptr)
            return true;
        return false;
    }
};

class BT {
    NODE *root;
    int m;
public:
    BT();

    NODE *getRoot() { return root; }
    int getM() { return m; }

    void setRoot(NODE *N) { root = N; }
    void setM(int M) { m = M; }
};

BT::BT() {
    root = nullptr;
    m = 0;
}

int binarySearch(vector<int> K, int n, int target) {
    int low = 0;
    int high = n - 1;
    int mid;

    while(low <= high) {
        mid = (low + high) / 2;

        if(K[mid] == target) {
            return mid;
        }
        else if(K[mid] > target) {
            high = mid - 1;
        }
        else if(K[mid] < target) {
            low = mid + 1;
        }
    }
    return low;
}

void insertBT(BT *T, int m, int newKey) {
    NODE *x = T->getRoot();
    NODE *y = nullptr;
    stack<NODE*> st;
    stack<int> ist;
    int i;

    while(!x->isNull()) {
        i = binarySearch(x->getK(), x->getN(), newKey);

        if (i < x->getN() && newKey == x->getK(i)) return;

        st.push(x);
        ist.push(i);

        x = x->getP(i);
    }

    while(!st.empty()) {
        x = st.top(); st.pop();
        i = ist.top(); ist.pop();

        if(x->getN() < m-1) {
            x->insertK(newKey);

            if(!y->isNull()) x->insertP(y);

            return;
        }

        NODE* tempNode = new NODE(m+1);
        tempNode->copyNode(x);
        tempNode->insertK(newKey);
        if(!y->isNull()) {
            tempNode->insertP(y);
        }

        y = new NODE(m);
        x->copyNodeFirst(tempNode);
        y->copyNodeSecond(tempNode);
        newKey = tempNode->getK(m/2);

        delete tempNode;
    }

    NODE* toRoot = new NODE(m);

    T->setRoot(toRoot);
    T->getRoot()->insertK(newKey);
    T->getRoot()->insertP(x);
    T->getRoot()->insertP(y);
}

void deleteBT(BT *T, int m, int oldKey) {
    NODE* x = T->getRoot();
    NODE* y = nullptr;
    NODE* internalNode = nullptr;
    NODE* bestSibling = nullptr;
    stack<NODE*> st;
    stack<int> ist;
    int i;

    while(!x->isNull()) {
        i = binarySearch(x->getK(), x->getN(), oldKey);

        if(i < x->getN() && oldKey == x->getK(i)) break;

        st.push(x);
        ist.push(i);
        x = x->getP(i);
    }

    if(x->isNull()) return;

    if(!x->getP(i+1)->isNull()) {
        internalNode = x;
        st.push(x);
        ist.push(i+1);
        x = x->getP(i+1);

        while(!x->isNull()) {
            st.push(x);
            ist.push(0);
            x = x->getP(0);
        }
    }

    if(x->isNull()) {
        x = st.top(); st.pop();
        internalNode->setK(i, x->getK(0));
        x->setK(0, oldKey);
        i = ist.top(); ist.pop();
    }

    x->deleteK(i);

    while(!st.empty()) {
        if(x->getN() >= (m-1)/2) return;

        y = st.top(); st.pop();
        i = ist.top(); ist.pop();
        int LorR = -1;
        bestSibling = y->bestSibling(i, LorR);
        int yi = i - LorR;

        if(bestSibling->getN() > (m-1)/2) {
            x->insertK(y->getK(yi));
            if(y->getK(yi) < bestSibling->getK(0)) {
                y->setK(yi, bestSibling->getK(0));
                bestSibling->deleteK(0);
                x->insertP(bestSibling->getP(0));
                bestSibling->deleteP(0);
            }
            else {
                y->setK(yi, bestSibling->getK(bestSibling->getN()-1));
                bestSibling->deleteK(bestSibling->getN()-1);
                x->insertP(bestSibling->getP(bestSibling->getN()));
                bestSibling->deleteP(bestSibling->getN());
            }
            break;
        }

        if(bestSibling->getK(0) < y->getK(yi)) {
            bestSibling->insertK(y->getK(yi));
            vector<int> mergeK = x->getK();
            vector<NODE*> mergeP = x->getP();
            for(int i=0; i<x->getN(); i++) {
                bestSibling->insertK(mergeK[i]);
            }
            for(int i=0; i<=x->getN(); i++) {
                bestSibling->insertP(mergeP[i]);
            }
            y->deleteK(yi);
            y->deleteP(yi+1);
        }
        else {
            x->insertK(y->getK(yi));
            vector<int> mergeK = bestSibling->getK();
            vector<NODE*> mergeP = bestSibling->getP();
            for(int i=0; i<bestSibling->getN(); i++) {
                x->insertK(mergeK[i]);
            }
            for(int i=0; i<=bestSibling->getN(); i++) {
                x->insertP(mergeP[i]);
            }
            y->deleteK(yi);
            y->deleteP(yi+1);
        }

        x = y;
    }

    if(x->getN() == 0) {
        T->setRoot(x->getP(0));
        delete x;
    }
}

void inorder(NODE *N) {
    if(N == nullptr) return;
    for(int i=0; i<N->getN(); i++) {
        if(N->getP(i) != nullptr) {
            // cout<<"down: ";
            inorder(N->getP(i));
        }
        cout<<N->getK(i)<<" ";
    }
    if(N->getP(N->getN()) != nullptr) {
        // cout<<"down: ";
        inorder(N->getP(N->getN()));
    }
    // cout<<"up: ";
}

void inorderBT(BT *T) {
    inorder(T->getRoot());
    cout<<endl;
}

int main() {
    BT* T = new BT();
    vector<int> insertNums;
    vector<int> deleteNums;

    ifstream inputInsert("insertSequence.txt");
    while(!inputInsert.eof()) {
        int n;
        inputInsert>>n;
        insertNums.push_back(n);
    }
    inputInsert.close();

    for(int i=0; i<insertNums.size(); i++) {
        insertBT(T, 3, insertNums[i]);
        inorderBT(T);
    }

    ifstream inputDelete("deleteSequence.txt");
    while(!inputDelete.eof()) {
        int n;
        inputDelete>>n;
        deleteNums.push_back(n);
    }
    inputDelete.close();

    for(int i=0; i<deleteNums.size(); i++) {
        deleteBT(T, 3, deleteNums[i]);
        inorderBT(T);
    }

    T = new BT();

    return 0;
}