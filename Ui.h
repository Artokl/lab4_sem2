#ifndef UI_H
#define UI_H

#include <iostream>

void StartMenu() {
    std::cout << "Hello user, which binarytree do you want to create, Int or Complex?" << std::endl;
    std::cout << "If you want to exit programm, enter Exit" << std::endl;
    std::cout << "Enter your command:";
}
void IntMenu() {
    std::cout << "There are some functions, that you can do with intbinarytree:" << std::endl;
    std::cout << "0) ReturnBack" << std::endl;
    std::cout << "1) RunTests" << std::endl;
    std::cout << "2) Map" << std::endl;
    std::cout << "3) Where" << std::endl;
    std::cout << "4) Reduce" << std::endl;
    std::cout << "5) Merge" << std::endl;
    std::cout << "6) FindSubTr" << std::endl;
    std::cout << "7) KLP" << std::endl;
    std::cout << "8) KPL" << std::endl;
    std::cout << "9) LPK" << std::endl;
    std::cout << "10) LKP" << std::endl;
    std::cout << "11) PLK" << std::endl;
    std::cout << "12) PKL" << std::endl;
}
void ComplexMenu() {
    std::cout << "There are some functions, that you can do with complexbinarytree:" << std::endl;
    std::cout << "0) ReturnBack" << std::endl;
    std::cout << "1) RunTests" << std::endl;
    std::cout << "2) Map" << std::endl;
    std::cout << "3) Reduce" << std::endl;
    std::cout << "4) Merge" << std::endl;
    std::cout << "5) FindSubTr" << std::endl;
    std::cout << "6) KLP" << std::endl;
    std::cout << "7) KPL" << std::endl;
    std::cout << "8) LPK" << std::endl;
    std::cout << "9) LKP" << std::endl;
    std::cout << "10) PLK" << std::endl;
    std::cout << "11) PKL" << std::endl;
}
#endif //UI_H
