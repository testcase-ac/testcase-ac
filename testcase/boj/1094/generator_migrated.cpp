#include <iostream>
#include <random>
#include <ctime>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,64);
    cout<<dist(gen);
}
