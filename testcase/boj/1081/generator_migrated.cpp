#include <iostream>
#include <random>
#include <ctime>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,2000000000);
    int a=dist(gen),b=dist(gen);
    if(a>b) swap(a,b);
    cout<<a<<' '<<b;
}
