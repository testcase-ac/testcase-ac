#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> small_dis(1,999);
    uniform_int_distribution<long long> large_dis(1001,100000000);
    uniform_int_distribution<int> flip(0, 1);
    int is_small = flip(gen);
    long long a, b;
    if (is_small) {
        a = small_dis(gen);
        b = small_dis(gen);
    } else {
        a = large_dis(gen);
        b = large_dis(gen);
    }
    cout << a << " " << b;
}
