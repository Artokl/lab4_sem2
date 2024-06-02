#ifndef PRINTTREE_H
#define PRINTTREE_H

#include "Tree.h"
#include <iostream>

// Вспомогательные функции для подсчета количества цифр
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
    count += 3; // для " + " и "i"
    return count;
}

// Вспомогательная функция для нахождения максимальной длины числа в дереве
template <typename T>
int getMaxDigits(Node<T>* node) {
    if (node == nullptr) return 0;
    int currentDigits = countDigits(node->GetValue());
    int leftDigits = getMaxDigits(node->GetLeft());
    int rightDigits = getMaxDigits(node->GetRight());
    int maxDigits = currentDigits > leftDigits ? currentDigits : leftDigits;
    return maxDigits > rightDigits ? maxDigits : rightDigits;
}

// Вспомогательная функция для нахождения глубины дерева
template <typename T>
int findMaxPathLength(Node<T>* node) {
    if (node == nullptr) return 0;
    int leftDepth = findMaxPathLength(node->GetLeft());
    int rightDepth = findMaxPathLength(node->GetRight());
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// Вспомогательная функция для возведения в степень
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// Вспомогательная функция для печати узлов дерева на текущем уровне
template <typename T>
void printLevel(Node<T>* node, int level, int indentSpace, int levelWidth, int nodeWidth, int lengthNode) {
    if (level == 1) {
        for (int i = 0; i < indentSpace; ++i) {
            std::cout << ' ';
        }
        if (node == nullptr) {
            for (int i = 0; i < lengthNode; ++i) {
                std::cout << '_';
            }
            for (int i = 0; i < nodeWidth; ++i) {
                std::cout << ' ';
            }
        }
        else {
            std::cout << node->GetValue();
            for (int i = 0; i < nodeWidth; ++i) {
                std::cout << ' ';
            }
        }
    }
    else if (level > 1) {
        if (node == nullptr) {
            printLevel(node, level - 1, indentSpace, levelWidth, nodeWidth, lengthNode);
            printLevel(node, level - 1, indentSpace, levelWidth, nodeWidth, lengthNode);
        }
        else {
            printLevel(node->GetLeft(), level - 1, indentSpace, levelWidth, nodeWidth, countDigits(node->GetValue()-1));
            printLevel(node->GetRight(), level - 1, indentSpace, levelWidth, nodeWidth, countDigits(node->GetValue()+1));
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

    int maxDepth = findMaxPathLength(head);
    int maxDigits = getMaxDigits(head);

    // Определяем ширину для каждого уровня
    int nodeWidth = maxDigits + 2; // Добавляем отступы для каждого числа
    int levelWidth = nodeWidth * power(2, maxDepth - 1);
    int a = 0, c = 50;
    for (int i = 1; i <= maxDepth; ++i) {
        for (int j = 1; j <= maxDepth - i; j++) {
            a += power(2,j);
        }
        int indentSpace = a;
        //int indentSpace = levelWidth / power(2, i) - nodeWidth / 2;
        if (maxDigits > 1 && i != maxDepth) {
            indentSpace += power(maxDigits,maxDepth - i - 1) ;
        }
        printLevel(head, i, indentSpace, levelWidth, c - indentSpace, countDigits(head->GetValue()));
        if (maxDigits == 1) c = indentSpace + 1;
        else c = indentSpace;
        a = 0;
        std::cout << std::endl;
    }
}

#endif // PRINTTREE_H












