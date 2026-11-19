#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

void add_vectors(size_t size, const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& c) {
    std::cout << "Vector size: " << size << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to add 2 int vectors in a function: " << duration << " ms" << std::endl;

    // std::cout << "The first 10 elements of the resulting vector are: ";
    // for (size_t i = 0; i < 10; ++i) {
    //     std::cout << c[i] << " ";
    // }
    // std::cout << std::endl;
}
void add_vectors(size_t size, const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
    std::cout << "Vector size: " << size << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // Data dependency: c[i] depends on c[i - 1], so we cannot vectorize this loop
    for (size_t i = 1; i < size; ++i) {
        c[i] = a[i] + c[i - 1];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to add 2 float vectors in a function: " << duration << " ms" << std::endl;

    // std::cout << "The first 10 elements of the resulting vector are: ";
    // for (size_t i = 0; i < 10; ++i) {
    //     std::cout << c[i] << " ";
    // }
    // std::cout << std::endl;
}

int main() {
    const size_t n = 10'000'000;
    std::vector<int> a(n), b(n), c(n);
    std::vector<float> af(n), bf(n), cf(n);

    std::iota(b.begin(), b.end(), 1);
    std::iota(c.begin(), c.end(), 1);
    std::iota(cf.begin(), cf.end(), 1.0f);
    std::iota(bf.begin(), bf.end(), 1.0f);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < n; i++) {
        a[i] = b[i] + c[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time taken to add 2 int vectors: " << duration << " ms" << std::endl;
    // std::cout << "The first 10 elements of the resulting vector are: ";
    // for (int i = 0; i < 10; i++) {
    //     std::cout << a[i] << " ";
    // }
    // std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; i++) {
        af[i] = bf[i] + cf[i];
    }

    end = std::chrono::high_resolution_clock::now();
    auto duration_float = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time taken to add 2 float vectors: " << duration_float << " ms" << std::endl;
    // std::cout << "The first 10 elements of the resulting vector are: ";
    // for (int i = 0; i < 10; i++) {
    //     std::cout << af[i] << " ";
    // }
    // std::cout << std::endl;

    add_vectors(n, b, c, a);
    add_vectors(n, bf, cf, af);
}
