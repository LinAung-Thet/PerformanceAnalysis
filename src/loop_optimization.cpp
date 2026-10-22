#include <iostream>
#include <chrono>

int main_() {
    auto start = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    long long n = 1'000'000'000;
    for (int i = 1; i <= n; i++)
        sum += i;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;

    start = std::chrono::high_resolution_clock::now();

    sum = (n * (n + 1)) / 2; // Using the formula for the sum of the first n natural numbers

    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken (optimized): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}