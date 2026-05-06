//GPT 코드 기반으로 약간 수정한 코드
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	random_device rd;
	mt19937_64 g(rd());
	
	uniform_int_distribution<int> dn(1,50);
	
	int n=dn(g),m=dn(g),l=dn(g);
	cout<<n<<' '<<m<<' '<<l<<'\n';
	
	ll lim=1000000000;
	vector<ll> h(n),w(m);
	
	ll s=0;
	for(int i=0;i<n;i++){
		ll r=uniform_int_distribution<ll>(1,min(lim/n*2,lim-s-(n-i-1)))(g);
		h[i]=r;
		s+=r;
	}
	
	s=0;
	for(int i=0;i<m;i++){
		ll r=uniform_int_distribution<ll>(1,min(lim/m*2,lim-s-(m-i-1)))(g);
		w[i]=r;
		s+=r;
	}
	
	for(int i=0;i<n;i++){
		cout<<h[i]<<(i+1<n?' ':'\n');
	}
	for(int i=0;i<m;i++){
		cout<<w[i]<<(i+1<m?' ':'\n');
	}
}
