//GPT 코드
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main() {
	random_device rd;
	mt19937_64 g(rd());
	
	uniform_int_distribution<int> dn(1,30);
	int n=dn(g);
	
	int mx=n*(n-1)/2;
	uniform_int_distribution<int> dm(0,mx);
	int m=dm(g);
	
	uniform_int_distribution<ll> dk(1,1000000000000000000LL);
	ll k=dk(g);
	
	vector<pair<int,int>> e;
	set<pair<int,int>> s;
	
	uniform_int_distribution<int> dv(1,n);
	while(s.size()<m) {
		int a=dv(g),b=dv(g);
		if(a==b) continue;
		if(a>b) swap(a,b);
		if(s.insert({a,b}).second) e.push_back({a,b});
	}
	
	cout<<n<<' '<<m<<' '<<k<<'\n';
	for(auto &p:e) cout<<p.first<<' '<<p.second<<'\n';
}
