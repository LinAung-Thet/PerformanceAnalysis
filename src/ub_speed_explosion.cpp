#include <iostream>
#include <array>
#include <span>
#include <vector>

std::string func(int x) {
    int dummy = 0;
    if ( x + 1 <= x)
        return "1";
    return "0";
}
void assign(int* arr, int n) {
    for (int i = 0; i <= n; ++i) {
        arr[i] = i;
    }

    std::cout << "Array assignment completed." << std::endl;
}
void printArray(int* arr, int n) {
    for (int i = 0; i <= n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void printSize(std::span<int> arr)
{
    std::cout << "Array size: " << arr.size() << std::endl;
}

template <std::size_t N>
void printSize(std::array<int, N>& arr)
{
    for (int i=0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::cout << "Array size: " << arr.size() << std::endl;
}

int main() {
    std::cout << "The result of func(INT_MAX) is: " + func(INT_MAX) << std::endl;

    std::cout << "The condition (x + 1 <= x) is optimized away by the compiler because it is assumed to be impossible." << std::endl;
    std::cout << "As a result, INT_MAX + 1 is never evaluated, and no overflow occurs." << std::endl;

    // // Demonstrating undefined behavior with a null pointer dereference
    // int* p = nullptr;
    // *p = 5;  // UB

    int arr[5];
    assign(arr, 5);  // This will cause undefined behavior due to out-of-bounds access
    printArray(arr, 5);

    // Using template.
    std::array<int, 5> arr2{};
    printSize(arr2);  

    // Using span.
    std::vector<int> arr3(5);
    printSize(arr3);

    return 0;
}
