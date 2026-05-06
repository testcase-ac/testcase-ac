#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-2000000000,2000000000);
    cout<<dis(gen)<<' '<<dis(gen);
}
