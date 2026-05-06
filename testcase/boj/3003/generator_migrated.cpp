#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    cout<<dis(gen)<<' '<<dis(gen)<<' '<<dis(gen)<<' '<<dis(gen)<<' '<<dis(gen)<<' '<<dis(gen);
    return 0;
}
