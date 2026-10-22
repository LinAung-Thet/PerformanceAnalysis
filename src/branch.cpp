#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

int main_() {

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10'000 - 1);
    
    std::vector<int> v(10'000'000);
    std::vector<int> r(10'000'000);

    std::generate(r.begin(), r.end(), [&]() {return dist(rng); });

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < v.size(); i++)
        v[i] = (r[i] % 8 == 0 ? 0 : 1);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill vector using branch: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << " seconds\n";

    auto no_branch_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < v.size(); i++) {
        v[i] = !(r[i] & 7);  // Using bitwise AND to avoid branching
    }
    auto no_branch_end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill vector (no branch): " << std::chrono::duration_cast<std::chrono::milliseconds>(no_branch_end - no_branch_start).count() << " ms" << std::endl;
    std::chrono::duration<double> no_branch_diff = no_branch_end - no_branch_start;
    std::cout << no_branch_diff.count() << " seconds\n";

    return 0;
}