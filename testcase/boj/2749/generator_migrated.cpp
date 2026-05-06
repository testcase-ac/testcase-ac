#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    
    uniform_int_distribution<long long> dist(1,1000000000000000000);
    cout<<dist(gen);
}
