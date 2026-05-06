#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
ll pwpw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%(M-1);
        a=a*a%(M-1);
        n/=2;
    } return r;
}
ll phi(ll n) {
    ll a=n;
    for(ll p=2;p*p<=n;p++) {
        if(n%p==0) a=a/p*(p-1);
        while(n%p==0) n=n/p;
    } return n==1?a:a/n*(n-1);
}
int main() {
    ll n,m,p=0,r=0;
    cin>>n>>m;
    ll t=pwpw(m,n-1);
    for(ll g=1;g*g<=m;g++) {
        if(m%g) continue;
        if(m/g%2) p=(p+pw(2,t*g)*phi(m/g))%M;
        if(g*g!=m&&g%2)p=(p+pw(2,t*m/g)*phi(g))%M;
    } p=p*pw(m,M-2)%M*pw(2,pwpw(m,n)*(M-2)%(M-1))%M;
    for(ll k=1;k<m;k++) {
        r=0;
        t=pwpw(k,n-1);
        for(ll g=1;g*g<=k;g++) {
            if(k%g) continue;
            if(k/g%2) r=(r+pw(2,t*g)*phi(k/g))%M;
            if(g*g!=k&&g%2) r=(r+pw(2,t*k/g)*phi(g))%M;
        } r=r*pw(k,M-2)%M*pw(2,pwpw(k,n)*(M-2)%(M-1))%M;
        if(p==r) {cout<<k;return 0;}
    } cout<<"Smart Oldbie";
}
