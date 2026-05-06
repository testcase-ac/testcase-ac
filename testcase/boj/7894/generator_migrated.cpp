#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<int> dist(1,10000000);
    uniform_int_distribution<int> num(1,10);
    int n=num(gen);
    cout<<n<<"\n";
    while(n--) cout<<dist(gen)<<"\n";
}
