#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> t(1,10),n(1,1000000);
    int T=t(g);
    cout<<T<<'\n';
    while(T--) {
        cout<<n(g)<<' '<<n(g)<<' '<<n(g)<<'\n';
    }
}
