#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1999;
int kitamasa(vector<int> c,vector<int> a,ll n) {
    int m=c.size();
    vector<int> s(m),t(m);
    s[0]=1;
    if(m!=1) t[1]=1;
    else t[0]=c[0];
    auto mul=[&c](vector<int> v,vector<int> w) {
        int m=v.size();
        vector<int> t(2*m);
        for(int j=0;j<m;j++) {
            for(int k=0;k<m;k++) {
                t[j+k]+=(ll)v[j]*w[k]%M;
                if(t[j+k]>=M) t[j+k]-=M;
            }
        } for(int j=2*m-1;j>=m;j--) {
            for(int k=1;k<=m;k++){
                t[j-k]+=(ll)t[j]*c[k-1]%M;
                if(t[j-k]>=M) t[j-k]-=M;
            }
        } t.resize(m);
        return t;
    }; while(n) {
        if(n&1) s=mul(s,t);
        t=mul(t,t);
        n>>=1;
    } ll r=0;
    for(int i=0;i<m;i++) r+=(ll)s[i]*a[i]%M;
    return r%M;
}
int main() {
    int n;
    ll m;
    cin>>n>>m;
    vector<int> a(n+1,0),c(n,1);
    a[0]=1;
    for(int i=1;i<=n;i++) for(int j=0;j<i;j++) a[i]=(a[i]+a[j])%M;
    c[n-1]=a[n];
    if(m<n) cout<<a[m];
    else cout<<kitamasa(c,a,m);
}
