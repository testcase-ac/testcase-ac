#include <iostream>
#include <random>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a * b / gcd(a, b);
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> gcd_dist(1,1000000);
    long long g = gcd_dist(gen);
    long long l = g;
    uniform_int_distribution<long long> factor_dist(1, 100000000 / g);
    long long factor = factor_dist(gen);
    l = g * factor;
    cout << g << " " << l << endl;
}
