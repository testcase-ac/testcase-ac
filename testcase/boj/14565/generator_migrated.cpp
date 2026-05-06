#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dist(2,1000000000000);
    long long n=dist(gen);
    uniform_int_distribution<long long> dis(1,n-1);
    cout<<n<<' '<<dis(gen);
}
