#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> ng(1,15);
    uniform_int_distribution<> xg(0,10000);
    int n=ng(gen);
    uniform_int_distribution<> tg(1,n);
    cout<<n<<' '<<tg(gen)<<"\n";
    for(int i=0;i<n-1;i++) cout<<xg(gen)<<' ';
    cout<<xg(gen);
}
