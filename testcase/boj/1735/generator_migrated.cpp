#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1,30000);
    cout<<dis(gen)<<" "<<dis(gen)<<endl<<dis(gen)<<" "<<dis(gen);
}
