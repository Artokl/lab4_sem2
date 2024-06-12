#ifndef TESTS_H
#define TESTS_H

#include "Tree.h"
#include <assert.h>
#include "complex.h"
#include "FunctionsForMapReduce.h"

void TestCreateTree()
{
    Tree<int> testInt;
    const int a[] = {6, 3, 9, 7, 10, 4};
    for (int i = 0; i < 6; i++) {
        testInt.Insert(a[i]);
    }
    assert(testInt.Find(6) != nullptr);
    assert(testInt.Find(3) != nullptr);
    assert(testInt.Find(9) != nullptr);
    assert(testInt.Find(7) != nullptr);
    assert(testInt.Find(10) != nullptr);
    assert(testInt.Find(4) != nullptr);
}
void TestCreateTreeComplex()
{
    Tree<complex> testInt;
    const complex a(2,1);
    const complex b(3,4);
    const complex c(1,5);
    const complex d(7,2);
    testInt.Insert(a);
    testInt.Insert(b);
    testInt.Insert(c);
    testInt.Insert(d);
    assert(testInt.Find(a) != nullptr);
    assert(testInt.Find(b) != nullptr);
    assert(testInt.Find(c) != nullptr);
    assert(testInt.Find(d) != nullptr);
}
void TestFindSubTree()
{
    Tree<int> testInt;
    const int a[] = {6, 3, 9, 7, 10, 4};
    for (int i = 0; i < 6; i++) {
        testInt.Insert(a[i]);
    }
    Tree<int> testInt1 = testInt.FindSubTree(9);
    assert(testInt1.Find(9) != nullptr);
    assert(testInt1.Find(7) != nullptr);
    assert(testInt1.Find(10) != nullptr);
}
void TestFindSubTreeComplex()
{
    Tree<complex> testInt;
    const complex a(2,1);
    const complex b(3,4);
    const complex c(1,5);
    const complex d(7,2);
    testInt.Insert(a);
    testInt.Insert(b);
    testInt.Insert(c);
    testInt.Insert(d);
    Tree<complex> testInt1 = testInt.FindSubTree(complex(3,4));
    assert(testInt1.Find(complex(3,4)) != nullptr);
    assert(testInt1.Find(complex(7,2)) != nullptr);
}
void TestIsSubtreeInTree() {
    Tree<int> testInt;
    const int a[] = {6, 3, 9, 7, 10, 4};
    for (int i = 0; i < 6; i++) {
        testInt.Insert(a[i]);
    }
    const Tree<int> testInt1 = testInt.FindSubTree(9);
    assert(testInt.IsSubtreeInTree(testInt1));
}
void TestIsSubtreeInTreeComplex() {
    Tree<complex> testInt;
    const complex a(2,1);
    const complex b(3,4);
    const complex c(1,5);
    const complex d(7,2);
    testInt.Insert(a);
    testInt.Insert(b);
    testInt.Insert(c);
    testInt.Insert(d);
    const Tree<complex> testInt1 = testInt.FindSubTree(complex(3,4));
    assert(testInt.IsSubtreeInTree(testInt1));
}
void TestIsElemInTree() {
    Tree<int> testInt;
    const int a[] = {6, 3, 9, 7, 10, 4};
    for (int i = 0; i < 6; i++) {
        testInt.Insert(a[i]);
    }
    assert(testInt.IsElemInTree(4));
}
void TestIsElemInTreeComplex() {
    Tree<complex> testInt;
    const complex a(2,1);
    const complex b(3,4);
    const complex c(1,5);
    const complex d(7,2);
    testInt.Insert(a);
    testInt.Insert(b);
    testInt.Insert(c);
    testInt.Insert(d);
    assert(testInt.IsElemInTree(complex(7,2)));
}
void TestMapFunc() {
    const int a[] = {6, 3, 9, 7, 10, 4};
    Tree<int> testInt;
    for (int i = 0; i < 6; i++) {
        testInt.Insert(a[i]);
    }
    testInt.Map(&MapFunc);
    assert(testInt.Find(12) != nullptr);
    assert(testInt.Find(6) != nullptr);
    assert(testInt.Find(18) != nullptr);
    assert(testInt.Find(14) != nullptr);
    assert(testInt.Find(20) != nullptr);
    assert(testInt.Find(8) != nullptr);
}
void TestWhereFunc()
{
    const int a[] = {6, 3, 9, 7, 10, 4};
    Tree<int> testInt;
    for (int i = 0; i < 6; i++)
    {
        testInt.Insert(a[i]);
    }
    testInt.Where(&WhereFunc);
    assert(testInt.Find(6) != nullptr);
    assert(testInt.Find(10) != nullptr);
    assert(testInt.Find(4) != nullptr);
    assert(testInt.Find(3) == nullptr);
    assert(testInt.Find(9) == nullptr);
    assert(testInt.Find(7) == nullptr);
}
void TestReduceFunc()
{
    const int a[] = {6, 3, 9, 7, 10, 4};
    Tree<int> testInt;
    for (int i = 0; i < 6; i++)
    {
        testInt.Insert(a[i]);
    }
    const int result = testInt.Reduce(&ReduceFunc);
    assert(result == 39);
}
void TestMergeTree() {
    const int a[] = {6, 3, 9, 7, 10, 4};
    Tree<int> testInt;
    for (int i = 0; i < 6; i++)
    {
        testInt.Insert(a[i]);
    }
    const int b[] = {6, 2, 8, 7, 4};
    Tree<int> testInt1;
    for (int i = 0; i < 5; i++)
    {
        testInt1.Insert(b[i]);
    }
    testInt.Merge(testInt1);
    assert(testInt.Find(12) != nullptr);
    assert(testInt.Find(5) != nullptr);
    assert(testInt.Find(8) != nullptr);
    assert(testInt.Find(17) != nullptr);
    assert(testInt.Find(14) != nullptr);
    assert(testInt.Find(10) != nullptr);
}
void TestMergeTreeComplex() {
    Tree<complex> testInt;
    const complex a(2,1);
    const complex b(3,4);
    const complex c(1,5);
    const complex d(7,2);
    testInt.Insert(a);
    testInt.Insert(b);
    testInt.Insert(c);
    testInt.Insert(d);
    Tree<complex> testInt1;
    const complex a1(5,2);
    const complex b1(3,8);
    const complex c1(2,4);
    const complex d1(9,1);
    testInt1.Insert(a1);
    testInt1.Insert(b1);
    testInt1.Insert(c1);
    testInt1.Insert(d1);
    testInt.Merge(testInt1);
    assert(testInt.Find(complex(7,3)) != nullptr);
    assert(testInt.Find(complex(12,5)) != nullptr);
    assert(testInt.Find(complex(4,13)) != nullptr);
    assert(testInt.Find(complex(2,4)) != nullptr);
    assert(testInt.Find(complex(7,2)) != nullptr);
}
void Tests() {
    TestCreateTree();
    TestCreateTreeComplex();
    TestFindSubTree();
    TestFindSubTreeComplex();
    TestIsSubtreeInTree();
    TestIsSubtreeInTreeComplex();
    TestIsElemInTree();
    TestIsElemInTreeComplex();
    TestMapFunc();
    TestWhereFunc();
    TestReduceFunc();
    TestMergeTree();
    TestMergeTreeComplex();
}


#endif //TESTS_H
