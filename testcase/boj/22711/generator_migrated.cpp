#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> T(1,20),n(1,10000);
    int t=T(g);
    while(t--) cout<<n(g)<<'\n';
    cout<<"0\n";
}
