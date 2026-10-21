#include <iostream>
#include <chrono>
#include <span>

void muladd(int* a, 
    const int* b, 
    const int* c, 
    const int n) 
{
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] + b[i] * c[i];
    }
}
void muladd_no_alias(int* __restrict a, 
    const int* __restrict b, 
    const int* __restrict c, 
    const int n) 
{
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] + b[i] * c[i];
        // a[i] = std::fma(b[i], c[i], a[i]); // Use fused multiply-add for better performance
    }
}
void muladd_span(std::span<int> a, 
    std::span<const int> b, 
    std::span<const int> c) 
{
    for (int i = 0; i < a.size(); ++i) {
        a[i] += b[i] * c[i];
    }
}

int main() {
    const int n = 100'000'000;
    int* a = new int[n];
    int* b = new int[n];
    int* c = new int[n];

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = i + 1;
        c[i] = i + 2;
    }

    auto start = std::chrono::high_resolution_clock::now();
    muladd(a, b, c, n);
    // muladd_span(std::span<int>(a, n), std::span<const int>(b, n), std::span<const int>(c, n));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = i + 1;
        c[i] = i + 2;
    }

    auto start_no_alias = std::chrono::high_resolution_clock::now();
    muladd_no_alias(a, b, c, n);
    auto end_no_alias = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken (no aliasing): " << std::chrono::duration_cast<std::chrono::milliseconds>(end_no_alias - start_no_alias).count() << " ms" << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;

    // std::cout << __cplusplus << "\n";
    // std::cout << "_MSVC_LANG: " << _MSVC_LANG << '\n';
    
    return 0;
}