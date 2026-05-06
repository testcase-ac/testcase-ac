#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<int> v(1000001,0);
ll sqfree(ll x) {
	ll cnt=0;
	for(ll i=1;i*i<=x;i++)
		cnt+=v[i]*(x/(i*i));
	return cnt;
}
int main() {
	v[1]=1;
	for(int i=1;i<1000001;i++) {
		if(v[i]) {
			for(int j=i+i;j<1000001;j+=i)
				v[j]-=v[i];
		}
	} ll k;
	cin>>k;
	ll l=0,r=100000000000;
	while (l<r-1) {
		ll m=(l+r)/2;
		if(m-sqfree(m)<k) l=m;
		else r=m;
	} cout<<r;
}
