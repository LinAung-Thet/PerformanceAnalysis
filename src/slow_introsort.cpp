#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<chrono>
#include<random>

int main(){
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 10'000 - 1);
    
    std::vector<int> v(10'000'000);

    std::generate(v.begin(), v.end(), [&]() { return dist(rng); });
 
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to sort random vector: " << duration << " ms" << std::endl;

    std::reverse(v.begin(), v.end());

    start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to sort reverse previously random vector: " << duration << " ms" << std::endl;

    std::iota(v.begin(), v.end(), 0);

    start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to sort sequential vector: " << duration << " ms" << std::endl;

    std::reverse(v.begin(), v.end());

    start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time taken to sort reverse previously sequential vector: " << duration << " ms" << std::endl;

    std::cout << "Among the four cases, the worst case is sorting a random vector, while the best case is sorting the reverse of a previously sequential vector." << std::endl;
    std::cout << "The other two cases are in between, with neither consistently outperforming the other." << std::endl;   
    
    return 0;
}