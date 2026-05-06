#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> d(1,9);
    int n=d(gen);
    cout<<n<<"\n";
    while(n--) cout<<d(gen)<<','<<d(gen)<<"\n";
}
