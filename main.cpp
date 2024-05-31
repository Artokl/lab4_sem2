#include <iostream>
#include <limits>

#include "Tests.h"
#include "Ui.h"
#include "PrintTree.h"
#include "StrSwitchCase.h"

int main() {
    StartMenu();
    int flag = 1;
    Tree<complex> testComplex;
    Tree<int> testInt;
    int a, size = 0;
    complex b;
    std::string command;
    int intReduceRes;
    complex ComplexReduceRes;
    while (flag) {
        std::cin >> command;
        SWITCH(command) {
            CASE("Exit"):
            {
                flag = 0;
                std::cout << "Programm ended";
                break;
            }
            CASE("Int"):
            {
                std::cout << "If you want to stop entering elements, enter stop\n";
                while(!std::cin.fail()) {
                    std::cout<<"Enter your element" << std::endl;
                    std::cin >> a;
                    if (!std::cin.fail()) testInt.insert(a), size++;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Your tree:\n";
                printTree(testInt);
                IntMenu();
                int flag1 = 1;
                std::string command1;
                while(flag1) {
                    std::cin >> command1;
                    SWITCH(command1) {
                        CASE("ReturnBack"):
                        {
                            flag1 = 0;
                            break;
                        }
                        CASE("RunTests"):
                        {
                            Tests();
                            std::cout << "Tests passed" << std::endl;
                            break;
                        }
                        CASE("Map"):
                        {
                            const Tree<int> testInt1 = testInt;
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            testInt.map(MapFunc);
                            std::cout << "ResultTree:" << std::endl;
                            printTree(testInt);
                            testInt = testInt1;
                            break;
                        }
                        CASE("Where"):
                        {
                            const Tree<int> testInt1 = testInt;
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            testInt.where(WhereFunc);
                            std::cout << "ResultTree:" << std::endl;
                            printTree(testInt);
                            testInt = testInt1;
                            break;
                        }
                        CASE("Reduce"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            intReduceRes = testInt.reduce(ReduceFunc);
                            std::cout << "Result:" << intReduceRes << std::endl;
                            break;
                        }
                        CASE("Merge"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            Tree<int> testInt2 = testInt;
                            Tree<int> testInt1;
                            std::cout << "Let's create a second tree for merging\n";
                            std::cout << "If you want to stop entering elements, enter stop\n";
                            while(!std::cin.fail()) {
                                std::cout<<"Enter your element" << std::endl;
                                std::cin >> a;
                                if (!std::cin.fail()) testInt1.insert(a);
                            }
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Your second tree:\n";
                            printTree(testInt1);
                            testInt.merge(testInt1);
                            std::cout << "Your result tree:\n";
                            printTree(testInt);
                            testInt = testInt2;
                            break;
                        }
                        CASE("FindSubTr"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            std::cout << "Enter the number starting from which you need to find the subtree:\n";
                            std::cin >> a;
                            Tree<int>testInt1 = testInt.FindSubTree(a);
                            std::cout << "Your result tree:\n";
                            printTree(testInt1);
                            break;
                        }
                        CASE("KLP"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::KLP, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("KPL"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::KPL, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("LPK"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::LPK, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("LKP"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::LKP, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("PLK"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::PLK, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("PKL"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testInt);
                            int result[size];
                            testInt.traverseTree(traverse::PKL, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        DEFAULT:
                        {
                            std::cout << "Unknown command" << std::endl;
                            break;
                        }
                    }
                    if (command1 != "ReturnBack") IntMenu();
                }
                size = 0;
                break;
            }
            CASE("Complex"):
            {
                std::cout << "If you want to stop entering elements, enter stop in Im\n";
                while(!std::cin.fail()) {
                    std::cout<<"Enter your element" << std::endl;
                    std::cin >> b;
                    if (!std::cin.fail()) testComplex.insert(b), size++;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Your tree:\n";
                printTree(testComplex);
                ComplexMenu();
                int flag1 = 1;
                std::string command1;
                while(flag1) {
                    std::cin >> command1;
                    SWITCH(command1) {
                        CASE("ReturnBack"):
                        {
                            flag1 = 0;
                            break;
                        }
                        CASE("RunTests"):
                        {
                            Tests();
                            std::cout << "Tests passed" << std::endl;
                            break;
                        }
                        CASE("Map"):
                        {
                            const Tree<complex> testComplex1 = testComplex;
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            testComplex.map(MapFunc);
                            std::cout << "ResultTree:" << std::endl;
                            printTree(testComplex);
                            testComplex = testComplex1;
                            break;
                        }
                        CASE("Reduce"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            ComplexReduceRes = testComplex.reduceCompl(ReduceFunc);
                            std::cout << "Result:" << ComplexReduceRes << std::endl;
                            break;
                        }
                        CASE("Merge"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            const Tree<complex> testComplex2 = testComplex;
                            Tree<complex> testComplex1;
                            std::cout << "Let's create a second tree for merging\n";
                            std::cout << "If you want to stop entering elements, enter stop\n";
                            while(!std::cin.fail()) {
                                std::cout<<"Enter your element" << std::endl;
                                std::cin >> b;
                                if (!std::cin.fail()) testComplex1.insert(b);
                            }
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Your second tree:\n";
                            printTree(testComplex1);
                            testComplex.merge(testComplex1);
                            std::cout << "Your result tree:\n";
                            printTree(testComplex);
                            testComplex = testComplex2;
                            break;
                        }
                        CASE("FindSubTr"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            std::cout << "Enter the number starting from which you need to find the subtree:\n";
                            std::cin >> b;
                            Tree<complex>testComplex1 = testComplex.FindSubTree(b);
                            std::cout << "Your result tree:\n";
                            printTree(testComplex1);
                            break;
                        }
                        CASE("KLP"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::KLP, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("KPL"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::KPL, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("LPK"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::LPK, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("LKP"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::LKP, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("PLK"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::PLK, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        CASE("PKL"):
                        {
                            std::cout << "OriginalTree:" << std::endl;
                            printTree(testComplex);
                            complex result[size];
                            testComplex.traverseTree(traverse::PKL, result);
                            std::cout << "Result: ";
                            for (int i = 0; i < size; ++i) {
                                std::cout << result[i] << " ";
                            }
                            std::cout << std::endl;
                            break;
                        }
                        DEFAULT:
                        {
                            std::cout << "Unknown command" << std::endl;
                            break;
                        }
                    }
                    if (command1 != "ReturnBack") ComplexMenu();
                }
                size = 0;
                break;
            }
            DEFAULT:
            {
                std::cout << "Unknown command" << std::endl;
                break;
            }
        }
        if (command != "Exit") StartMenu();
    }
    return 0;
}
