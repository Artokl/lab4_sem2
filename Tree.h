#ifndef TREE_H
#define TREE_H

#include "complex.h"

template<typename T>
class Node {
private:
    T node_;
    Node* right_;
    Node* left_;

    void SetLeft(Node* node) {
        left_ = node;
    }

    void SetRight(Node* node) {
        right_ = node;
    }

    void SetData(T value) {
        this->node_ = value;
    }

    template<typename> friend class Tree;
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

    ~Node() {
        right_ = nullptr;
        left_ = nullptr;
    }
};

enum class Traverse {
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
    void DeleteTree(Node<T> *elem) {
        if (elem == nullptr)
        {
            return;
        }
        DeleteTree(elem->GetLeft());
        DeleteTree(elem->GetRight());
        delete elem;
    }

    Node<T>* CopyTree(Node<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Node<T>* newNode = new Node<T>(node->GetValue());
        newNode->SetLeft(CopyTree(node->GetLeft()));
        newNode->SetRight(CopyTree(node->GetRight()));
        return newNode;
    }

    Node<T>* DeleteNode(Node<T>* root, T value) {
        if (root == nullptr) return root;
        if (value < root->GetValue()) {
            root->SetLeft(DeleteNode(root->GetLeft(), value));
        }
        else if (value > root->GetValue()) {
            root->SetRight(DeleteNode(root->GetRight(), value));
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
            Node<T>* temp = FindMin(root->GetRight());
            root->SetData(temp->GetValue());
            root->SetRight(DeleteNode(root->GetRight(), temp->GetValue()));
        }
        return root;
    }

    Node<T>* FindMin(Node<T>* node) {
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
        if (!func(root->GetValue())) this->DeleteElem(root->GetValue());
    }

    void FuncReduce(Node<T>* root, T(*func)(T, T), T* base) {
        if (root == nullptr) return;
        FuncReduce(root->GetLeft(), func, base);
        FuncReduce(root->GetRight(), func, base);
        *base = func(root->GetValue(), *base);
    }

    Node<T>* MergeTrees(Node<T>* node1, Node<T>* node2) {
        if (node1 == nullptr) return CopyTree(node2);
        if (node2 == nullptr) return CopyTree(node1);
        node1->SetData(node1->GetValue() + node2->GetValue());
        node1->SetLeft(MergeTrees(node1->GetLeft(), node2->GetLeft()));
        node1->SetRight(MergeTrees(node1->GetRight(), node2->GetRight()));
        return node1;
    }

    void StoreInOrder(Node<T>* node, Node<T>* arr[], int* index) {
        if (node == nullptr) return;
        StoreInOrder(node->GetLeft(), arr, index);
        arr[(*index)++] = node;
        StoreInOrder(node->GetRight(), arr, index);
    }

    void QuickSort(Node<T>* arr[], const int left, const int right) {
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
        if (left < j) QuickSort(arr, left, j);
        if (i < right) QuickSort(arr, i, right);
    }

    Node<T>* BuildBalancedTree(Node<T>* arr[], const int start, const int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        Node<T>* root = arr[mid];
        root->SetLeft(BuildBalancedTree(arr, start, mid - 1));
        root->SetRight(BuildBalancedTree(arr, mid + 1, end));
        return root;
    }

    void CorrectTree() {
        if (head_ == nullptr) return;
        int numNodes = CountNodes(head_);
        Node<T>** nodesArray = new Node<T>*[numNodes];
        int index = 0;
        StoreInOrder(head_, nodesArray, &index);
        QuickSort(nodesArray, 0, numNodes - 1);
        head_ = BuildBalancedTree(nodesArray, 0, numNodes - 1);
        delete[] nodesArray;
    }

    int CountNodes(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + CountNodes(node->GetLeft()) + CountNodes(node->GetRight());
    }

    void TraverseKLP(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        result[index++] = node->GetValue();
        TraverseKLP(node->GetLeft(), result, index);
        TraverseKLP(node->GetRight(), result, index);
    }

    void TraverseKPL(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        result[index++] = node->GetValue();
        TraverseKPL(node->GetRight(), result, index);
        TraverseKPL(node->GetLeft(), result, index);
    }

    void TraverseLPK(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        TraverseLPK(node->GetLeft(), result, index);
        TraverseLPK(node->GetRight(), result, index);
        result[index++] = node->GetValue();
    }

    void TraverseLKP(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        TraverseLKP(node->GetLeft(), result, index);
        result[index++] = node->GetValue();
        TraverseLKP(node->GetRight(), result, index);
    }

    void TraversePLK(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        TraversePLK(node->GetRight(), result, index);
        TraversePLK(node->GetLeft(), result, index);
        result[index++] = node->GetValue();
    }

    void TraversePKL(Node<T>* node, T* result, int& index) {
        if (node == nullptr) return;
        TraversePKL(node->GetRight(), result, index);
        result[index++] = node->GetValue();
        TraversePKL(node->GetLeft(), result, index);
    }
    Node<T> *InsertPrivate(Node<T> *root, T value) {
        if (root == nullptr)
            return new Node<T>(value);
        else if (value < root->GetValue())
            root->SetLeft(InsertPrivate(root->GetLeft(), value));
        else if (value > root->GetValue())
            root->SetRight(InsertPrivate(root->GetRight(), value));
        return root;
    }
public:
    Tree () : head_(nullptr) {}

    explicit Tree (Node<T>* head) : head_(head) {}

    Tree(const Tree& other) {
        head_ = CopyTree(other.head_);
    }

    Tree &operator=(const Tree& other) {
        if (this == &other) {
            return *this;
        }
        DeleteTree(head_);
        head_ = CopyTree(other.head_);
        return *this;
    }

    ~Tree() {
        DeleteTree(this->GetHead());
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
            Node<T>* subtreeRoot = CopyTree(root_);
            return Tree(subtreeRoot);
        }
        return Tree(nullptr);
    }

    bool IsElemInTree(T value) {
        return Find(value) ? true : false;
    }

    bool CmpTraverse(Node<T> *first, Node<T> *second) const {
        if (first == nullptr && second == nullptr)
            return true;
        if (first == nullptr || second == nullptr)
            return false;
        if (first->GetValue() != second->GetValue())
            return false;
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

    void Insert(T value) {
        head_ = this->InsertPrivate(this->GetHead(),value);
    }

    void Map(T (*func)(T))
    {
        this->FuncMap(this->GetHead(), func);
    }

    void Where(bool(*func)(int))
    {
        this->FuncWhere(this->GetHead(), func);
    }

    int Reduce(T (*func)(T, T))
    {
        int result = 0;
        this->FuncReduce(this->GetHead(), func, &result);
        return result;
    }

    complex ReduceCompl(T (*func)(T, T))
    {
        complex result(0, 0);
        this->FuncReduce(this->GetHead(), func, &result);
        return result;
    }

    void DeleteElem(T value) {
        head_ = DeleteNode(head_, value);
    }

    void Merge(const Tree& other) {
        head_ = MergeTrees(head_, other.GetHead());
        CorrectTree();
    }

    void TraverseTree(const Traverse order, T* result) {
        int index = 0;
        switch (order) {
            case Traverse::KLP:
                TraverseKLP(head_, result, index);
            break;
            case Traverse::KPL:
                TraverseKPL(head_, result, index);
            break;
            case Traverse::LPK:
                TraverseLPK(head_, result, index);
            break;
            case Traverse::LKP:
                TraverseLKP(head_, result, index);
            break;
            case Traverse::PLK:
                TraversePLK(head_, result, index);
            break;
            case Traverse::PKL:
                TraversePKL(head_, result, index);
            break;
        }
    }

    void Clear() {
        DeleteTree(head_);
        head_ = nullptr;
    }
};

#endif //TREE_H
