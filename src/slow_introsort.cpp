#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

int main(){
    std::vector<int> v(10'000'000);
    std::iota(v.begin(), v.end(), 0);
    std::reverse(v.begin(), v.end());

    std::sort(v.begin(), v.end());
}