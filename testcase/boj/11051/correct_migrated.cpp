#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll c[1001][1001];
vector<int> luca(ll n,int m) {
    vector<int> v;
    while(n) {
        v.push_back(n%m);
        n/=m;
    } return v;
}
ll com(int n,int k,int m) {
    if(n<k) return 0;
    if(n/2<k) k=n-k;
    ll &r=c[n][k];
    if(r!=-1) return r;
    if(k==0) return r=1;
    if(k==1) return r=n;
    return r=(com(n-1,k-1,m)+com(n-1,k,m))%m;
}
ll mdcm(ll n,ll k,int m) {
    memset(c,-1,sizeof(c));
    ll r=1;
    vector<int> a,b;
    a=luca(n,m);b=luca(k,m);
    int j=min(a.size(),b.size());
    for(int i=0;i<j;i++) {
        int n=a[i],x=b[i];
        r*=com(n,x,m);
        r%=m;
    } return r;
}
int main() {
    ll n,k;
    cin>>n>>k;
    cout<<mdcm(n,k,10007);
}
