#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll mul(ll a,ll b,ll m) {
    long double x=(long double)a*b/m;
    ll c=(ll)(x);
    __int128 r=(__int128)a*b-(__int128)c*m;
    if(r<0) r+=m;
    else if(r>=(__int128)m) r-=m;
    return (ll)r;
}
ll pw(__int128 x,__int128 y,__int128 m) {
    x%=m;
    __int128 r=1;
    while(y) {
        if(y%2) r=mul(r,x,m);
        x=mul(x,x,m);
        y/=2;
    } return (ll)r;
}
bool chk(ll n,ll a) {
    if(a%n==0) return 1;
    ll k=n-1;
    while(1) {
        ll t=pw(a,k,n);
        if(t==n-1) return 1;
        if(k%2) return (t==1||t==n-1);
        k/=2;
    }
}
bool isprime(ll n) {
    if(n==2||n==3) return 1;
    if(n%2==0) return 0;
    ll a[]={2,3,5,7,11};
    for(int i=0;i<5;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<long long> p(2,1000000000);
    long long P;
    while(1) {
        P=p(g);
        if(isprime(P)) break;
    } cout<<g()%(P-1)+1<<' '<<P;
}
