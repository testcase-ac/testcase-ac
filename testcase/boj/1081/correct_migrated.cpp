#include <bits/stdc++.h>
#define ll long long
using namespace std;
void cnt(ll n,vector<ll>& r) {
    ll f=1;
    while(f<=n) {
        ll l=n-(n/f)*f,m=(n/f)%10,h=n/(f*10);
        for(int i=0;i<=9;i++) {
            if(i<m) r[i]+=(h+1)*f;
            else if(i==m) r[i]+=h*f+l+1;
            else r[i]+=h*f;
        } f*=10;
    }
}
int main() {
    ll n,m,k=0;
    cin>>n>>m;
    n--;
    vector<ll> r(10,0),s(10,0);
    cnt(n,r);
    cnt(m,s);
    for(int i=0;i<=int(log10(n));i++) r[0]-=int(pow(10,i));
    for(int i=0;i<=int(log10(m));i++) s[0]-=int(pow(10,i));
    for(int i=0;i<10;i++) k+=(s[i]-r[i])*i;
    cout<<k;
}
