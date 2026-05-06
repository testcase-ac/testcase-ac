#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=7340033;
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
int nth(vector<int> x,ll n) {
    if(n<x.size()) return x[n];
    vector<int> v=berlekamp_massey(x);
    if(v.empty()) return 0;
    return get_nth(v,x,n);
}
int main() {
    vector<int> v={1,2,4,4,6,10,12,14,22,26,30,44,56,70,98,130,162,216,292,358,470,628,792,1050,1384,1788,2334,3072,3974,5162,6784,8786,11420,14992,19484,25388,33160,43262,56252,73392,95798,124496,162556,212048,275976,360154,469694,611844,797628,1040344,1355550,1766402,2304368,3002354,3913802,5103798,6651808,1330929,3964467,56364,4526934,3020079,3283660,5845937,4089463,6249217,6173168,5434618,6035817,3277472,599541,2502130,101659,1046904,615205,4310505,7073937,1528843,1573423,628109,3338517,7141678,6639170,7199721,2508559,6983719,3226808,1362909,4057445,5216401,4789473,7148607,3490252,3859839,3919928,4410603,1774464,5030371,3213868,3673656,2253480,162153,6967672,6212357,1488891,5272969,2288129,3900589,6122846,6177603,475903,151346,4687899,1154734,4168110,1744680,1925769,3198859,1886183,702652,4959058,6769965,4832688,6752128,5192022,872961,2974929,4528640,4768052,929662,5895668,7181370,6213930,7284455,594448,3091509,5305389,2707419,3941867,1121753,845827,3309438,595600,781040};
    long long n;
    cin>>n;
    cout<<nth(v,n);
}
