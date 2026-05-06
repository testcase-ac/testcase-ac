#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    uniform_int_distribution<> dis(1, 100000);
    int a=dis(gen);
    uniform_int_distribution<> bis(1, a);
    cout<<a<<' '<<bis(gen)<<' '<<dis(gen);
}
