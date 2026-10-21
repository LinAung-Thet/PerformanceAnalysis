#include <iostream>
#include <chrono>
#include <span>
#include <cmath>
#include <immintrin.h>

void muladd(float* a, 
    const float* b, 
    const float* c, 
    const int n) 
{
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] + b[i] * c[i];
    }
}
void muladd_no_alias(float* __restrict a, 
    const float* __restrict b, 
    const float* __restrict c, 
    const int n) 
{
    for (int i = 0; i < n; ++i) {
        a[i] = a[i] + b[i] * c[i];
        // a[i] = std::fma(b[i], c[i], a[i]); // Use fused multiply-add for better performance
    }
}
void muladd_fma(float* __restrict a,
                const float* __restrict b,
                const float* __restrict c,
                int n)
{
    for (int i = 0; i < n; i += 8) {
        __m256 va = _mm256_load_ps(a + i);
        __m256 vb = _mm256_load_ps(b + i);
        __m256 vc = _mm256_load_ps(c + i);

        __m256 r = _mm256_fmadd_ps(vb, vc, va);

        _mm256_store_ps(a + i, r);
    }
}
void muladd_span(std::span<float> a, 
    std::span<const float> b, 
    std::span<const float> c) 
{
    for (int i = 0; i < a.size(); ++i) {
        a[i] += b[i] * c[i];
    }
}

int main() {
    const int n = 100'000'000;
    float* a = new float[n];
    float* b = new float[n];
    float* c = new float[n];

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = (float)i;
        b[i] = (float)(i + 1);
        c[i] = (float)(i + 2);
    }

    auto start = std::chrono::high_resolution_clock::now();
    muladd(a, b, c, n);
    // muladd_span(std::span<float>(a, n), std::span<const float>(b, n), std::span<const float>(c, n));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = (float)i;
        b[i] = (float)(i + 1);
        c[i] = (float)(i + 2);
    }

    auto start_no_alias = std::chrono::high_resolution_clock::now();
    // muladd_no_alias(a, b, c, n);
    muladd_fma(reinterpret_cast<float*>(a), reinterpret_cast<float*>(b), reinterpret_cast<float*>(c), n);
    auto end_no_alias = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken (no aliasing): " << std::chrono::duration_cast<std::chrono::milliseconds>(end_no_alias - start_no_alias).count() << " ms" << std::endl;

    delete[] a;
    delete[] b;
    delete[] c;

    // std::cout << __cplusplus << "\n";
    // std::cout << "_MSVC_LANG: " << _MSVC_LANG << '\n';
    
    return 0;
}