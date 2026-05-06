#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
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
int nth(vector<int> v,vector<int> x,ll n) {
    if(n<v.size()) return v[n];
    if(x.empty()) return 0;
    return get_nth(x,v,n);
}
int main() {
    vector<int> v={31,197},x={7,1000000003};
    int t;
    ll n;
    cin>>t;
    while(t--) {
        cin>>n;
        cout<<nth(v,x,n-2)<<'\n';
    }
}
