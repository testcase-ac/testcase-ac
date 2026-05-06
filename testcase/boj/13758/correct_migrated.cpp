#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=30011;
void fwht_xor(vector<ll> &a,bool inv) {
    ll n=a.size(),h=(M+1)/2;
    for(int i=2,j=1;i<=n;i<<=1,j<<=1) {
        for(int k=0;k<n;k+=i) {
            for(int l=0;l<j;l++) {
                int t=a[j+k+l];
                a[j+k+l]=a[k+l]-t;
                a[k+l]+=t;
                if(inv) a[j+k+l]=a[j+k+l]*h%M,a[k+l]=a[k+l]*h%M;
            }
        }
    }
}
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    int n,k;
    cin>>n>>k;
    vector<ll> a(k+1,1);
    int N=1;
    while(N<a.size()) N<<=1;
    a.resize(N);
    fwht_xor(a,0);
    for(auto&i:a) i=pw(i,n);
    fwht_xor(a,1);
    ll s=0;
    for(int i=1;i<a.size();i++) s=(s+a[i])%M;
    cout<<(s+M)%M;
}
