#include <iostream>
#include <random>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distn(1,7);
    int n=distn(gen);
    uniform_int_distribution<int> distm(1,n);
    cout<<n<<' '<<distm(gen);
}
