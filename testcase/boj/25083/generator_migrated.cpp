#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);

    int n = dis(gen);
    cout<<n;
    return 0;
}
