#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+1;
vector<ll> p(N,-1);
vector<bool> isp(N,1);
ll pw(ll a,ll n,ll m) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%m;
        a=a*a%m;
        n/=2;
    } return r;
}
ll psqrt(ll n,ll p) {
    if(n==0) return 0;
    if(p==2) return n%2;
    if(pw(n,(p-1)/2,p)!=1) return -1;
    int k=0;
    while((p-1)%(2<<k)==0) k++;
    ll t=1<<k,w=1;
    while(pw(w,(p-1)/2,p)==1) w++;
    w=pw(w,(p-1)/t,p);
    ll m=pw(n,(p-1)/t,p),s=1;
    for(int i=k-2;i>=0;i--) {
        if(pw(m,1<<i,p)!=1) {
            s=s*w%p;
            m=(m*w%p)*w%p;
        } w=w*w%p;
    } ll r=s*pw(n,(p+t-1)/(2*t),p)%p;
    if(r*r%p==n) return r;
    return -1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=2;i*i<N;i++) if(isp[i]) for(int j=i*i;j<N;j+=i) isp[j]=0;
    for(int i=2;i<N;i++) if(isp[i]) {
        int x=psqrt(i-1,i);
        if(x==-1) continue;
        for(int j=x;j<N;j+=i) if(p[j]==-1) p[j]=i;
        x=i-x;
        for(int j=x;j<N;j+=i) if(p[j]==-1) p[j]=i;
    } int q;
    ll n;
    cin>>q;
    while(q--) {
        cin>>n;
        if(p[n]==-1||p[n]==n*n+1) {cout<<"-1\n";continue;}
        cout<<p[n]<<' '<<(n*n+1)/p[n]<<'\n';
    }
}
