#ifndef PRINTTREE_H
#define PRINTTREE_H

#include "Tree.h"
#include <iostream>

int countDigits(int number) {
    if (number == 0) return 1;
    int count = 0;
    if (number < 0) number = -number;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

int countDigits(const complex& number) {
    int count = 0;
    int a = number.GetRe();
    int b = number.GetIm();
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a == 0) count++;
    if (b == 0) count++;
    while (a != 0) {
        a /= 10;
        count++;
    }
    while (b != 0) {
        b /= 10;
        count++;
    }
    count += 3;
    return count;
}

template <typename T>
int getMaxDigits(Node<T>* node) {
    if (node == nullptr) return 0;
    const int currentDigits = countDigits(node->GetValue());
    const int leftDigits = getMaxDigits(node->GetLeft());
    const int rightDigits = getMaxDigits(node->GetRight());
    const int maxDigits = currentDigits > leftDigits ? currentDigits : leftDigits;
    return maxDigits > rightDigits ? maxDigits : rightDigits;
}

template <typename T>
int findMaxPathLength(Node<T>* node) {
    if (node == nullptr) return 0;
    const int leftDepth = findMaxPathLength(node->GetLeft());
    const int rightDepth = findMaxPathLength(node->GetRight());
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int power(const int base, const int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

template <typename T>
void printLevel(Node<T>* node, const int level, int indentSpace, int nodeWidth, int lengthNode) {
    if (level == 1) {
        for (int i = 0; i < indentSpace; ++i) std::cout << ' ';
        if (node == nullptr) {
            for (int i = 0; i < lengthNode; ++i) std::cout << '_';
            for (int i = 0; i < nodeWidth; ++i) std::cout << ' ';
        }
        else {
            std::cout << node->GetValue();
            for (int i = 0; i < nodeWidth; ++i) std::cout << ' ';
        }
    }
    else if (level > 1) {
        if (node == nullptr) {
            printLevel(node, level - 1, indentSpace, nodeWidth, lengthNode);
            printLevel(node, level - 1, indentSpace, nodeWidth, lengthNode);
        }
        else {
            printLevel(node->GetLeft(), level - 1, indentSpace, nodeWidth, countDigits(node->GetValue()-1));
            printLevel(node->GetRight(), level - 1, indentSpace, nodeWidth, countDigits(node->GetValue()+1));
        }
    }
}

template <typename T>
void printTree(Tree<T>& tree) {
    Node<T>* head = tree.GetHead();
    if (!head) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    const int maxDepth = findMaxPathLength(head);
    const int maxDigits = getMaxDigits(head);
    int a = 0, c = 50;
    for (int i = 1; i <= maxDepth; ++i) {
        for (int j = 1; j <= maxDepth - i; j++) a += power(2,j);
        int indentSpace = a;
        if (maxDigits > 1 && i != maxDepth) indentSpace += power(maxDigits,maxDepth - i - 1);
        printLevel(head, i, indentSpace, c - indentSpace, countDigits(head->GetValue()));
        if (maxDigits == 1) c = indentSpace + 1;
        else c = indentSpace;
        a = 0;
        std::cout << std::endl;
    }
}

#endif // PRINTTREE_H












