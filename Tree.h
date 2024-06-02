#ifndef TREE_H
#define TREE_H

#include "complex.h"

template<typename T>
class Node {
private:
    T node_;
    Node* right_;
    Node* left_;
public:
    Node() : node_(0), right_(nullptr), left_(nullptr) {}

    explicit Node(T value) : node_(value), right_(nullptr), left_(nullptr) {}

    T GetValue() {
        return node_;
    }

    Node *GetRight() {
        return right_;
    }

    Node *GetLeft() {
        return left_;
    }

    void setLeft(Node *node) {
        left_ = node;
    }

    void setRight(Node *node) {
        right_ = node;
    }

    void SetData(T value) {
        this->node_ = value;
    }

    ~Node() {
        right_ = nullptr;
        left_ = nullptr;
    }
};

enum class traverse {
    KLP,
    KPL,
    LPK,
    LKP,
    PLK,
    PKL
};

template <typename T>
class Tree {
private:
    Node<T>* head_;

    void deleteTree(Node<T> *elem) {
        if (elem == nullptr)
        {
            return;
        }
        deleteTree(elem->GetLeft());
        deleteTree(elem->GetRight());
        delete elem;
    }

    Node<T>* copyTree(Node<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node<T>* newNode = new Node<T>(node->GetValue());
        newNode->setLeft(copyTree(node->GetLeft()));
        newNode->setRight(copyTree(node->GetRight()));
        return newNode;
    }

    Node<T>* deleteNode(Node<T>* root, T value) {
        if (root == nullptr) return root;
        if (value < root->GetValue()) {
            root->setLeft(deleteNode(root->GetLeft(), value));
        }
        else if (value > root->GetValue()) {
            root->setRight(deleteNode(root->GetRight(), value));
        }
        else {
            if (root->GetLeft() == nullptr) {
                Node<T>* temp = root->GetRight();
                delete root;
                return temp;
            }
            else if (root->GetRight() == nullptr) {
                Node<T>* temp = root->GetLeft();
                delete root;
                return temp;
            }
            Node<T>* temp = findMin(root->GetRight());
            root->SetData(temp->GetValue());
            root->setRight(deleteNode(root->GetRight(), temp->GetValue()));
        }
        return root;
    }

    Node<T>* findMin(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->GetLeft() != nullptr) {
            current = current->GetLeft();
        }
        return current;
    }
    
    void FuncMap(Node<T> *root, T (*func)(T)) {
        if (root == nullptr) return;
        FuncMap(root->GetLeft(), func);
        FuncMap(root->GetRight(), func);
        root->SetData(func(root->GetValue()));
    }

    void FuncWhere(Node<T> *root, bool (*func)(T)) {
        if (root == nullptr) return;
        FuncWhere(root->GetLeft(), func);
        FuncWhere(root->GetRight(), func);
        if (!func(root->GetValue())) this->deleteElem(root->GetValue());
    }

    void FuncReduce(Node<T>* root, T(*func)(T, T), T* base) {
        if (root == nullptr) return;
        FuncReduce(root->GetLeft(), func, base);
        FuncReduce(root->GetRight(), func, base);
        *base = func(root->GetValue(), *base);
    }

    Node<T>* mergeTrees(Node<T>* node1, Node<T>* node2) {
        if (node1 == nullptr) return copyTree(node2);
        if (node2 == nullptr) return copyTree(node1);
        node1->SetData(node1->GetValue() + node2->GetValue());
        node1->setLeft(mergeTrees(node1->GetLeft(), node2->GetLeft()));
        node1->setRight(mergeTrees(node1->GetRight(), node2->GetRight()));
        return node1;
    }

    void storeInOrder(Node<T>* node, Node<T>* arr[], int* index) {
        if (node == nullptr) return;
        storeInOrder(node->GetLeft(), arr, index);
        arr[(*index)++] = node;
        storeInOrder(node->GetRight(), arr, index);
    }

    void quickSort(Node<T>* arr[], const int left, const int right) {
        int i = left, j = right;
        Node<T>* pivot = arr[(left + right) / 2];
        while (i <= j) {
            while (arr[i]->GetValue() < pivot->GetValue()) i++;
            while (arr[j]->GetValue() > pivot->GetValue()) j--;
            if (i <= j) {
                Node<T>* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        if (left < j) quickSort(arr, left, j);
        if (i < right) quickSort(arr, i, right);
    }

    Node<T>* buildBalancedTree(Node<T>* arr[], const int start, const int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        Node<T>* root = arr[mid];
        root->setLeft(buildBalancedTree(arr, start, mid - 1));
        root->setRight(buildBalancedTree(arr, mid + 1, end));
        return root;
    }

    void correctTree() {
        if (head_ == nullptr) return;
        int numNodes = countNodes(head_);
        Node<T>** nodesArray = new Node<T>*[numNodes];
        int index = 0;
        storeInOrder(head_, nodesArray, &index);
        quickSort(nodesArray, 0, numNodes - 1);
        head_ = buildBalancedTree(nodesArray, 0, numNodes - 1);
        delete[] nodesArray;
    }

    int countNodes(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->GetLeft()) + countNodes(node->GetRight());
    }

    void traverseKLP(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        result[index++] = node->GetValue();
        traverseKLP(node->GetLeft(), result, index);
        traverseKLP(node->GetRight(), result, index);
    }

    void traverseKPL(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        result[index++] = node->GetValue();
        traverseKPL(node->GetRight(), result, index);
        traverseKPL(node->GetLeft(), result, index);
    }

    void traverseLPK(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        traverseLPK(node->GetLeft(), result, index);
        traverseLPK(node->GetRight(), result, index);
        result[index++] = node->GetValue();
    }

    void traverseLKP(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        traverseLKP(node->GetLeft(), result, index);
        result[index++] = node->GetValue();
        traverseLKP(node->GetRight(), result, index);
    }

    void traversePLK(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        traversePLK(node->GetRight(), result, index);
        traversePLK(node->GetLeft(), result, index);
        result[index++] = node->GetValue();
    }

    void traversePKL(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        traversePKL(node->GetRight(), result, index);
        result[index++] = node->GetValue();
        traversePKL(node->GetLeft(), result, index);
    }
public:
    Tree () : head_(nullptr) {}

    explicit Tree (Node<T>* head) : head_(head) {}

    Tree(const Tree& other) {
        head_ = copyTree(other.head_);
    }

    Tree &operator=(const Tree& other) {
        if (this == &other) {
            return *this;
        }
        deleteTree(head_);
        head_ = copyTree(other.head_);
        return *this;
    }

    ~Tree() {
        deleteTree(this->GetHead());
    }

    Node<T> *Find(T value) {
        Node<T> *current = head_;
        while (current) {
            if (current->GetValue() == value)
                break;
            if (!current->GetLeft() && !current->GetRight())
                return nullptr;
            if (current->GetValue() > value)
                current = current->GetLeft();
            else
                current = current->GetRight();
        }
        return current;
    }

    Tree FindSubTree(T value) {
        Node<T>* root_ = Find(value);
        if (root_ != nullptr) {
            Node<T>* subtreeRoot = copyTree(root_);
            return Tree(subtreeRoot);
        }
        return Tree(nullptr);
    }

    bool IsElemInTree(T value) {
        return Find(value) ? true : false;
    }

    bool CmpTraverse(Node<T> *first, Node<T> *second) const {
        if (first == nullptr && second == nullptr) return true;
        if (first == nullptr || second == nullptr) return false;
        if (first->GetValue() != second->GetValue()) return false;
        return CmpTraverse(first->GetLeft(), second->GetLeft()) &&
               CmpTraverse(first->GetRight(), second->GetRight());
    }

    bool IsSubtreeInTree(Tree t) {
        auto res = Find(t.GetHead()->GetValue());
        if (!res) return false;
        return CmpTraverse(res, t.GetHead());
    }

    Node<T> *GetHead() const {
        return head_;
    }

    Node<T> *insertation(Node<T> *root, T value) {
        if (root == nullptr) return new Node<T>(value);
        else if (value < root->GetValue()) root->setLeft(insertation(root->GetLeft(), value));
        else if (value > root->GetValue()) root->setRight(insertation(root->GetRight(), value));
        return root;
    }

    void insert(T value) {
        head_ = this->insertation(this->GetHead(),value);
    }

    void map(T (*func)(T))
    {
        this->FuncMap(this->GetHead(), func);
    }

    void where(bool(*func)(int))
    {
        this->FuncWhere(this->GetHead(), func);
    }

    int reduce(T (*func)(T, T))
    {
        int result = 0;
        this->FuncReduce(this->GetHead(), func, &result);
        return result;
    }

    complex reduceCompl(T (*func)(T, T))
    {
        complex result(0, 0);
        this->FuncReduce(this->GetHead(), func, &result);
        return result;
    }

    void deleteElem(T value) {
        head_ = deleteNode(head_, value);
    }

    void merge(const Tree& other) {
        head_ = mergeTrees(head_, other.GetHead());
        correctTree();
    }

    void traverseTree(const traverse order, T* result) {
        int index = 0;
        switch (order) {
            case traverse::KLP:
                traverseKLP(head_, result, index);
            break;
            case traverse::KPL:
                traverseKPL(head_, result, index);
            break;
            case traverse::LPK:
                traverseLPK(head_, result, index);
            break;
            case traverse::LKP:
                traverseLKP(head_, result, index);
            break;
            case traverse::PLK:
                traversePLK(head_, result, index);
            break;
            case traverse::PKL:
                traversePKL(head_, result, index);
            break;
        }
    }

    void clear() {
        deleteTree(head_);
        head_ = nullptr;
    }
};

#endif //TREE_H
