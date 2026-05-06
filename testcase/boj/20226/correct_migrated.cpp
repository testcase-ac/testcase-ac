#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull pw(__int128 x, __int128 y, __int128 m) {
	x%=m;
	__int128 r=1;
	while(y) {
		if(y%2) r=(r*x)%m;
		x=(x*x)%m;
		y/=2;
	} return (ull)r;
}
bool chk(ull n, ull a) {
	if(a%n==0) return 1;
	ull k=n-1;
	while(1) {
		ull t=pw(a,k,n);
		if(t==n-1) return 1;
		if(k%2) return (t==1||t==n-1);
		k/=2;
	}
}
bool isprime(ull n) {
	if(n==2||n==3) return 1;
	if(n%2==0) return 0;
	ull a[]={2,3,5,7,11,13,17,19,23};
	for(int i=0;i<9;i++) if(!chk(n,a[i])) return 0;
	return 1;
}
ull gcd(ull a, ull b) {return b?gcd(b,a%b):a;}
ull dv(__int128 n) {
	if(n%2==0) return 2;
	if(isprime(n)) return n;
	__int128 x=rand()%(n-2)+2,y=x,c=rand()%10+1,g=1;
	while(g==1) {
		x=(x*x%n+c)%n;
		y=(y*y%n+c)%n;
		y=(y*y%n+c)%n;
		g=gcd(abs(x-y),n);
		if(g==n) return dv(n);
	} return isprime(g)?g:dv(g);
}
vector<pair<ull,int>> asdf(vector<ull>& v) {
	map<ull,int> m;
	for(auto& i:v) m[i]++;
	return vector<pair<ull,int>>(m.begin(),m.end());
}
void dfs(int d,ull k,const vector<pair<ull,int>>& f,vector<ull>& fac) {
	if(d==f.size()) {
		fac.push_back(k);
		return;
	} ull t=1;
	for(int i=0;i<=f[d].second;i++) {
		dfs(d+1,k*t,f,fac);
		t*=f[d].first;
	}
}
ull solve(ull n) {
	ull r=n+2;
	if(isprime(n)) return r;
	vector<ull> v;
	ull x=n;
	while(x>1) {
		ull d=dv(x);
		v.push_back(d);
		x/=d;
	} sort(v.begin(),v.end());
	auto f=asdf(v);
	vector<ull> fac;
	dfs(0,1,f,fac);
	sort(fac.begin(),fac.end());
	for(int i=0;i<fac.size();i++) {
		int t=lower_bound(fac.begin(),fac.end(),sqrt(fac[i]))-fac.begin();
		for(int j=t-3;j<=t+3;j++) {
			if(j<0||j>=fac.size()) continue;
			if(fac[i]%fac[j]) continue;
			r=min(r,n/fac[i]+fac[i]/fac[j]+fac[j]);
		}
	} return r;
}
int main() {
	ull n;
	while(cin>>n) {
	    if(!n) return 0;
	    cout<<solve(n)<<'\n';
	}
}
