#include <bits/stdc++.h>
#define ll long long
using namespace std;
bool f=0;
ll mul(ll a,ll b,ll m) {
	ll r=a*b-m*(ll)(1.L/m*a*b);
	return r+m*(r<0)-m*(r>=m);
}
ll p;
pair<ll,ll> fib(ll n,ll m){
	if(!n) return {0,1%m};
	auto t=fib(n>>1,m);
	ll a=t.first,b=t.second;
	ll c=mul(a,(2*b% m-mul(p% m,a,m)+m)%m,m);
	ll d=(mul(a,a,m)+mul(b,b,m))%m;
	if(n&1) return {d,(mul(p% m,d,m)+c)%m};
	return {c,d};
}
ll fibo(ll n,ll m) {return fib(n,m).first;}
ll per_prime_pow(ll pr,int e) {
	ll pe=1;
	for(int i=0;i<e;i++) pe*=pr;
	ll t=1;
	while(1){
		if(fib(t,pr)==make_pair(0LL,1LL)) break;
		t++;
	} ll cur=t;
	ll mod=pr;
	for(int i=2;i<=e;i++) {
		mod*=pr;
		if(fib(cur,mod)!=make_pair(0LL,1LL)) cur*=pr;
	} return cur;
}
int main() {
    int T;
    cin>>T;
    for(int t=1;t<=T;t++) {
        ll m;
        string s;
        cin>>p>>m>>s;
        cout<<"Case #"<<t<<": ";
        int k=s.length();
        ll mod=1,ss=stoll(s);
        for(int i=0;i<k;i++) mod*=10;
        ll LL[k+1],L[k+1];
        for(int i=1;i<=k;i++) {
            ll l2=per_prime_pow(2,i);
            ll l5=per_prime_pow(5,i);
            L[i]=lcm(l2,l5);
        } for(int i=1;i<=k;i++) {
            ll x=3;
            for(int t=0;t<i;t++) x*=10;
            x=max(x,300000LL);
            pair<ll,ll> tmp={0,1};
            while(1) {
                if(x%2||fib(x,L[i])!=tmp) {x*=2;break;}
                x/=2;
            } while(1) {
                if(x%5||fib(x,L[i])!=tmp) {x*=5;break;}
                x/=5;
            } while(1) {
                if(x%3||fib(x,L[i])!=tmp) {x*=3;break;}
                x/=3;
            } LL[i]=x;
        } vector<ll> v;
        for(int i=0;i<L[1];i++) if(fibo(i,10)==ss%10) v.push_back(i);
        for(ll i=100,id=2;i<=mod;i*=10,id++) {
            vector<ll> t;
            for(ll j:v) {
                for(ll k=0;k<L[id]/L[id-1];k++) if(fibo(j+k*L[id-1],i)==ss%i) t.push_back(j+k*L[id-1]);
            } v.swap(t);
            if(i==mod) break;
        } vector<ll> r;
        set<ll> st1;
        for(ll j:v) st1.insert(j%L[1]);
        for(int i=0;i<LL[1];i++) for(ll j:st1) if(fibo(i,L[1])==j%L[1]) r.push_back(i);
        for(ll i=100,id=2;i<=mod;i*=10,id++) {
            vector<ll> t;
            set<ll> st;
            for(ll j:v) st.insert(j%L[id]);
            for(ll j:r) {
                for(ll k=0;k<LL[id]/LL[id-1];k++) for(ll x:st) {
                    if(fibo(j+k*LL[id-1],L[id])==x%L[id]) t.push_back(j+k*LL[id-1]);
                }
            } r.swap(t);
            if(i==mod) break;
        } vector<ll> rr;
        vector<__int128> fib;
        fib.push_back(0);fib.push_back(1);
        for(int i=2;;i++) {
            fib.push_back((__int128)fib[i-1]*p+fib[i-2]);
            if(fib[i]>=mod/10) break;
        } ll lim=0;
        for(int i=0;;i++) if(fib[i]+1>=fib.size()) {lim=i;break;}
        for(ll i:r) {
            f=0;
            ll j=i%LL[k];
            j+=((m-j+LL[k]-1)/LL[k])*LL[k];
            if(s[0]=='0'&&j<lim) j+=((lim-j+LL[k]-1)/LL[k])*LL[k];
            if(fibo(fibo(j,L[k]),mod)==ss) rr.push_back(j);
        } sort(rr.begin(),rr.end());
        if(rr.empty()) cout<<"-1\n";
        else {
            sort(rr.begin(),rr.end());
            cout<<(ll)rr[0]<<'\n';
        } 
    }
}
