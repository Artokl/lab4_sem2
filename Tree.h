#ifndef TREE_H
#define TREE_H

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
    KLP = 0,
    KPL = 1,
    LPK = 2,
    LKP = 3,
    PLK = 4,
    PKL = 5
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
        if (root == nullptr) {
            return root;
        }
        if (value < root->GetValue()) {
            root->setLeft(deleteNode(root->GetLeft(), value));
        } else if (value > root->GetValue()) {
            root->setRight(deleteNode(root->GetRight(), value));
        } else {
            if (root->GetLeft() == nullptr) {
                Node<T>* temp = root->GetRight();
                delete root;
                return temp;
            } else if (root->GetRight() == nullptr) {
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
    
    void FuncMap(Node<T> *startRoot, T (*func)(T))
    {
        if (startRoot == nullptr)
        {
            return;
        }
        FuncMap(startRoot->GetLeft(), func);
        FuncMap(startRoot->GetRight(), func);
        startRoot->SetData(func(startRoot->GetValue()));
    }

    void FuncWhere(Node<T> *startRoot, bool (*func)(T))
    {
        if (startRoot == nullptr)
        {
            return;
        }
        FuncWhere(startRoot->GetLeft(), func);
        FuncWhere(startRoot->GetRight(), func);
        if (func(startRoot->GetValue()) == false)
        {
            this->deleteElem(startRoot->GetValue());
        }
    }

    void FuncReduce(Node<T>* startRoot, T(*func)(T, T), T* base)
    {
        if (startRoot == nullptr)
        {
            return;
        }
        FuncReduce(startRoot->GetLeft(), func, base);
        FuncReduce(startRoot->GetRight(), func, base);
        *base = func(startRoot->GetValue(), *base);
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
        while (current->GetLeft() || current->GetRight()) {
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

    void setRoot(Node<T> *newRoot) {
        head_ = newRoot;
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

    void deleteElem(T value) {
        head_ = deleteNode(head_, value);
    }
};

#endif //TREE_H
