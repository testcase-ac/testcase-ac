#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    ll n,r,m;
    cin>>n>>r>>m;
    vector<bool> prime(n+1,true);
    prime[0]=prime[1]=false;
    for(int i=2;i*i<=n;i++) {
        if(prime[i]) {
            for (int j=i*i;j<=n;j+=i) {
                prime[j] = false;
            }
        }
    } vector<ll> p;
    for(int i=2;i<=n;i++) {
        if(prime[i]) {
            p.push_back(i);
        }
    } vector<ll> s(p.size(),0);
    for(int i=0;i<p.size();i++) {
        for(ll j=p[i];j<=n;j*=p[i]) {
            s[i]+=(n/j)-(r/j)-((n-r)/j);
        }
    } ll com=1;
    for(int i=0;i<s.size();i++) {
        for(int j=0;j<s[i];j++) {
            com*=p[i];
            com%=m;
            if(com==0) {
                cout<<0;
                return 0;
            }
        }
    } cout<<com;
}
