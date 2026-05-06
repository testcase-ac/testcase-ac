#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<long long> n(1,1000000000000000000LL);
    int t=g()%10+1;
    cout<<t<<'\n';
    while(t--) {
        long long p=n(g),q;
        while(1) {
            q=n(g);
            if(gcd(p,q)==1) break;
        } cout<<p<<' '<<q<<'\n';
    }
}
