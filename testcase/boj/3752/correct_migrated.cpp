#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll phi(ll n) {
    ll a=n;
    for(ll p=2;p*p<=n;p++) {
        if(n%p==0) {
            a=a/p*(p-1);
            while(n%p==0) n=n/p;
        }
    } return n==1?a:a/n*(n-1);
}
int main() {
    int t,n;
    ll a,r;
    cin>>t;
    while(t--) {
        cin>>n;
        r=1;
        while(n--) {
            cin>>a;
            r=r*phi(a)%1000000007;
        } cout<<r<<'\n';
    }
}
