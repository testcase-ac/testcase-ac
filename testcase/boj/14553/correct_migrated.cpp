#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+9;
ll pw(ll a,ll n) {
	ll r=1;
	while(n) {
		if(n&1) r=r*a%M;
		a=a*a%M;
		n>>=1;
	} return r;
}
vector<int> berlekamp_massey(vector<int> x) {
	vector<int> ls,cur;
	int lf,ld;
	for(int i=0;i<x.size();i++){
		ll t=0;
		for(int j=0;j<cur.size();j++) t=(t+(ll)x[i-j-1]*cur[j])%M;
		if((t-x[i])%M==0) continue;
		if(cur.empty()) {
			cur.resize(i+1);
			lf=i;
			ld=(t-x[i])%M;
			continue;
		} ll k=-(x[i]-t)*pw(ld,M-2)%M;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j:ls) c.push_back(-j*k%M);
		if(c.size()<cur.size()) c.resize(cur.size());
		for(int j=0;j<cur.size();j++) c[j]=(c[j]+cur[j])%M;
		if(i-lf+(int)ls.size()>=(int)cur.size()) tie(ls,lf,ld)=make_tuple(cur,i,(t-x[i])%M);
		cur=c;
	} for(auto &i:cur) i=(i%M+M)%M;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, ll n){
	int m=rec.size();
	vector<int> s(m),t(m);
	s[0]=1;
	if(m!=1) t[1]=1;
	else t[0]=rec[0];
	auto mul=[&rec](vector<int> v,vector<int> w) {
		int m=v.size();
		vector<int> t(2*m);
		for(int j=0;j<m;j++){
			for(int k=0;k<m;k++){
				t[j+k]+=(ll)v[j]*w[k]%M;
				if(t[j+k]>=M) t[j+k]-=M;
			}
		} for(int j=2*m-1;j>=m;j--){
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
int guess_nth_term(vector<int> x,ll n){
	if(n<x.size()) return x[n];
	vector<int> v=berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v,x,n);
}
int main() {
    vector<int> v={1,4,12,38,125,414,1369,4522,14934,49322};
    int n;
    cin>>n;
    cout<<guess_nth_term(v,n-1);
}
