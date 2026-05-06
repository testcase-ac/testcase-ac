#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll M;
ll phi[1000001],g[1000001],l[1000001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    ll n,a=0,b=0;
    cin>>n>>M;
    for(int i=1;i<=n;i++) phi[i]=i;
    for(int i=2;i<=n;i++) {
        if(phi[i]==i) for(int j=i;j<=n;j+=i) phi[j]-=phi[j]/i;
    } for(int i=1;i<=n;i++) {
        for(int j=i;j<=n;j+=i) g[j]=(g[j]+phi[i]*(j/i))%M;
    } for(int i=1;i<=n;i++) {
        g[i]=(g[i]*2-i+M+g[i-1])%M;
        a+=g[i];
        a%=M;
    } for(int i=2;i<=n;i++) {
        for(int j=i;j<=n;j+=i) l[j]=(l[j]+phi[i]*i%M*j%M*(M+1)/2%M)%M;
    } for(int i=1;i<=n;i++) {
        l[i]=(l[i]*2+i+l[i-1])%M;
        b+=l[i];
        b%=M;
    } cout<<n*(n+1)%M*(n+2)%M*((n*n*3+n*6+1)%M)%M*pw(60,M-2)%M<<'\n'<<(a%M)*(b%M)%M;
}
