#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> n(1,100),r(1,100000000),xy(-100000000,100000000);
    int N=n(g);
    cout<<N<<' '<<r(g)<<'\n';
    while(N--) cout<<xy(g)<<' '<<xy(g)<<'\n';
}
