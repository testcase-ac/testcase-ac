#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distt(1,10);
    uniform_int_distribution<int> distn(1,1000000000);
    int t=distt(gen);
    cout<<t<<'\n';
    while(t--) {
        int n=distn(gen);
        uniform_int_distribution<int> distk(0,n);
        cout<<n<<' '<<distk(gen)<<'\n';
    }
}
