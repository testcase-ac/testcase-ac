#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> num(-9223372036854775807,9223372036854775807);
    uniform_int_distribution<int> tc(1,10);
    for(int i=0;i<3;i++) {
        int n=tc(gen);
        cout<<n<<"\n";
        while(n--) {
            cout<<num(gen)<<"\n";
        }
    }
}
