#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> arr;
int n;
bool chk(ll m) {
	ll a = 0, b = 0;
	multiset<ll, greater<ll>> st;
	for(ll t: arr)
		st.insert((t+m-1)/m);
	for(ll t=1; t<=n; t++) {
		ll& mn = a < b ? a : b, &mx = a > b ? a : b;
		auto mnit = st.lower_bound(t-mn), mxit = st.lower_bound(t-mx);
		if(mnit == st.end())
			return 0;
		if(*mnit == *st.begin()) {
			mn = t;
			st.erase(mnit);
		} else if(mxit != st.end()) {
			mx = t;
			st.erase(mxit);
		} else {
			mn = t;
			st.erase(mnit);
		}
	//	printf("now mn=%lld, mx=%lld\n", mn, mx);
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	arr.resize(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	ll l, r = 2e9+5;
	l = 1;
	while(l < r) {
		ll m = (l+r)/2;
		if(chk(m))
			r = m;
		else
			l = m+1;
	}
	cout << l;
}
