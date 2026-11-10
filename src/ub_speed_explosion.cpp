#include<iostream>

std::string func(int x) {
    int dummy = 0;
    if ( x + 1 <= x)
        return "1";
    return "0";
}

int main() {
    std::cout << "The result of func(INT_MAX) is: " + func(INT_MAX) << std::endl;

    std::cout << "The condition (x + 1 <= x) is optimized away by the compiler because it is assumed to be impossible." << std::endl;
    std::cout << "As a result, INT_MAX + 1 is never evaluated, and no overflow occurs." << std::endl;

    return 0;
}
