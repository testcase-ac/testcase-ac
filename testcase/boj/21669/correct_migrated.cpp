#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    ll n,m=0,x,a,b,c;
    cin>>n;
    x=sqrt((n-1)/6)+1;
    for(ll i=max(1LL,x-1000);i<=x;i++) {
        for(ll j=i;i*(j-1)*2<n;j++) {
            ll k=(n-i*j*2)/(i*2+j*2);
            if(j>k) break;
            if(m<i*j*k) {
                m=i*j*k;
                a=i,b=j,c=k;
            }
        }
    } cout<<m<<'\n'<<a<<' '<<b<<' '<<c;
}
