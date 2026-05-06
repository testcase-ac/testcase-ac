#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
vector<int> berlekamp_massey(vector<int> x) {
    vector<int> s,v;
    int f,d;
    for(int i=0;i<x.size();i++) {
        ll t=0;
        for(int j=0;j<v.size();j++) t=(t+(ll)x[i-j-1]*v[j])%M;
        if((t-x[i])%M==0) continue;
        if(v.empty()) {
            v.resize(i+1);
            f=i;
            d=(t-x[i])%M;
            continue;
        } ll k=-(x[i]-t)*pw(d,M-2)%M;
        vector<int> c(i-f-1);
        c.push_back(k);
        for(auto &j:s) c.push_back(-j*k%M);
        if(c.size()<v.size()) c.resize(v.size());
        for(int j=0;j<v.size();j++) c[j]=(c[j]+v[j])%M;
        if(i-f+(int)s.size()>=(int)v.size()) tie(s,f,d)=make_tuple(v,i,(t-x[i])%M);
        v=c;
    } for(auto &i:v) i=(i%M+M)%M;
    return v;
}
int get_nth(vector<int> rec,vector<int> dp,ll n) {
    int m=rec.size();
    vector<int> s(m),t(m);
    s[0]=1;
    if(m!=1) t[1]=1;
    else t[0]=rec[0];
    auto mul=[&rec](vector<int> v,vector<int> w) {
        int m=v.size();
        vector<int> t(2*m);
        for(int j=0;j<m;j++) {
            for(int k=0;k<m;k++) {
                t[j+k]+=(ll)v[j]*w[k]%M;
                if(t[j+k]>=M) t[j+k]-=M;
            }
        } for(int j=2*m-1;j>=m;j--) {
            for(int k=1;k<=m;k++){
                t[j-k]+=(ll)t[j]*rec[k-1]%M;
                if(t[j-k]>=M) t[j-k]-=M;
            }
        } t.resize(m);
        return t;
    }; while(n) {
        if(n&1) s=mul(s,t);
        t=mul(t,t);
        n>>=1;
    } ll r=0;
    for(int i=0;i<m;i++) r+=(ll)s[i]*dp[i]%M;
    return r%M;
}
int main() {
    cin.tie(0);
	vector<int> v={1,2,6,16,36,80,178,394,870};
	auto x=berlekamp_massey(v);
	ll n;
	while(cin>>n) {
	    if(n<=v.size()) cout<<v[n-1]<<'\n';
	    else cout<<get_nth(x,v,n-1)<<'\n';
	}
}
