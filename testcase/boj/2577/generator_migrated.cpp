#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> d(100,999);
    cout<<d(gen)<<"\n"<<d(gen)<<"\n"<<d(gen);
}
