#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distn(1,1000);
    uniform_int_distribution<int> distp(2,97);
    cout<<distn(gen)<<' '<<distp(gen);
}
