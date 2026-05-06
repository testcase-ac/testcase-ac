#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> d(1,1000000000000);
    cout<<d(gen);
}
