#include <iostream>
#include <thread>
#include <chrono>

struct S{
    int a;
    int b;
};
struct S_padded{
    int a;
    char padding[64 - sizeof(int)];
    int b;
};

int main_() {
    S s;
    S_padded s_padded;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1([&](){
        for (int i = 0; i < 100'000'000; i++) {
            s.a++;
        }
    });

    std::thread t2([&](){
        for (int i = 0; i < 100'000'000; i++) {
            s.b++;
        }
    });

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();

    std::thread t3([&](){
        for (int i = 0; i < 100'000'000; i++) {
            s_padded.a++;
        }
    });

    std::thread t4([&](){
        for (int i = 0; i < 100'000'000; i++) {
            s_padded.b++;
        }
    });

    t3.join();
    t4.join();

    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken (padded): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return 0;
}