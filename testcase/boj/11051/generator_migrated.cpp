#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distn(1,1000);
    int n=distn(gen);
    uniform_int_distribution<int> distk(0,n);
    cout<<n<<' '<<distk(gen);
}
