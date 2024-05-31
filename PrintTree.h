#ifndef PRINTTREE_H
#define PRINTTREE_H

#include "Tree.h"

template <typename T>
void printTree(Tree<T>& tree) {
    Node<T>* head_ = tree.GetHead();
    if (!head_) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }

    // We use a dynamic array to simulate queue behavior
    constexpr int maxNodes = 100; // Adjust this if the tree has more nodes
    Node<T>** nodes = new Node<T>*[maxNodes];
    int front = 0;
    int back = 0;

    // Start with the head node
    nodes[back++] = head_;

    while (front < back) {
        int nodeCount = back - front;

        while (nodeCount > 0) {
            if (Node<T>* node = nodes[front++]) {
                std::cout << node->GetValue() << " ";

                if (node->GetLeft()) nodes[back++] = node->GetLeft();
                if (node->GetRight()) nodes[back++] = node->GetRight();

                nodeCount--;
            }
            else std::cout << "  ";
        }
        std::cout << std::endl;
    }

    delete[] nodes;
}


#endif //PRINTTREE_H
