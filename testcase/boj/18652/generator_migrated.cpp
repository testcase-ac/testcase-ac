//GPT 코드
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rd(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

ll pw10(int k){
	ll r=1;
	while(k--)r*=10;
	return r;
}

int main(){
	int T=rd(1,30);
	cout<<T<<'\n';

	for(int tc=0;tc<T;tc++){
		ll P,m;
		int k;

		while(1){
			P=rd(1,(ll)1e18);
			ll g=gcd(P,(ll)1e18);
			if(g<5)break;
		}

		m=rd(1,(ll)1e18);
		k=rd(1,18);

		ll lim=pw10(k)-1;
		ll v=rd(0,lim);

		string s=to_string(v);
		while((int)s.size()<k)s='0'+s;

		cout<<P<<' '<<m<<' '<<s<<'\n';
	}
}
