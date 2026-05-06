#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> n(1,50),ab(1,1000000000);
    int N=n(g);
    cout<<N<<'\n';
    while(N--) cout<<ab(g)<<' '<<ab(g)<<'\n';
}
