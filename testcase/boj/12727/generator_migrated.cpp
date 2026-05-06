#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> t(1,100);
    uniform_int_distribution<int> n(2,30);
    int T=t(gen);
    cout<<T<<"\n";
    while(T--) cout<<n(gen)<<"\n";
}
