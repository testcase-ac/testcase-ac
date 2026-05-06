#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);
    cout<<dis(gen)<<"\n"<<dis(gen);
}
