#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll mul(ll a,ll b,ll m) {
	ll r=a*b-m*(ll)(1.L/m*a*b);
	return r+m*(r<0)-m*(r>=m);
}
ll pw(ll a,ll n,ll m) {
    ll r=1;
    while(n) {
        if(n%2) r=mul(r,a,m);
        a=mul(a,a,m);
        n/=2;
    } return r;
}
double f(int x) {
    double r=0;
    ll j;
    for(ll i=0;n*4-i*6>=0;i++) {
        ll t=(i*6+x)*(i*6+x);
        r+=(double)(pw(2,n*4-i*6,t*8)*9)/(t*8);
        j=i;
    } for(ll i=j+1;i<j+10;i++) {
        r+=pow(2,n*4-i*6)*9/((i*6+x)*(i*6+x)*8);
    } return r;
}
int main() {
    cin>>n;
    n--;
    double r=fmod(f(1)*16-f(2)*24-f(3)*8-f(4)*6+f(5),1);
    if(r<0) r+=1.0;
    long ans=r*16;
    cout<<uppercase<<hex<<ans;
}
