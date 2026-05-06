#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<long long> a(0,1000000000000000000LL);
    uniform_int_distribution<long long> b(1,1000000000000000000LL);
    uniform_int_distribution<int> c(1,100000000);
    cout<<b(g)<<' '<<a(g)<<' '<<a(g)<<' '<<a(g)<<' '<<b(g)<<' '<<c(g);
}
