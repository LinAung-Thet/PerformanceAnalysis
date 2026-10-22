#include <cstddef>
#include <iostream>

struct A {
    char c;
    int  i;
    double d;
};

struct B {
    char c;
    double d;
    int  i;
};

int main_() {
    std::cout << offsetof(A, c) << "\n";
    std::cout << offsetof(A, i) << "\n";
    std::cout << offsetof(A, d) << "\n";
    std::cout << sizeof(A) << "\n";

    std::cout << offsetof(B, c) << "\n";
    std::cout << offsetof(B, d) << "\n";
    std::cout << offsetof(B, i) << "\n";
    std::cout << sizeof(B) << "\n";
}