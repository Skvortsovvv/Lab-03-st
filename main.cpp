#include "Header.h"
#include <iostream>
int main() {
    
    SA(Function, 7, 10, 10000, 0.1);
    std::cout << std::endl;
    SA(ModifiedFun, 7, 10, 1000, 0.1);
}