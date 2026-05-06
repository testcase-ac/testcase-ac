#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> T(1,20),n(2,12),k(1,1000000000);
    int t=T(g);
    cout<<t<<'\n';
    while(t--) cout<<n(g)<<' '<<k(g)<<'\n';
}
