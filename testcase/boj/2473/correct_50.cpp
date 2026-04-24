#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll ans = LLONG_MAX, ansv[3] = {1,2,3};
void update(ll a, ll b, ll c) {
	ll s = a+b+c;
	if(abs(s) < ans) {
		ans = abs(s);
		ll t[] = {a,b,c};
		sort(t, t+3);
		memcpy(ansv, t, sizeof t);
	}
}
void f(vector<ll> &one, vector<ll> &two) {
	int n = one.size(), m = two.size();
	if(m < 2) return;
	for(int i=0; i<m; i++) {
		for(int j=i+1; j<m; j++) {
			ll s = two[i]+two[j];
			int k = lower_bound(one.begin(), one.end(), -s)-one.begin();
			if(k < n)
				update(one[k], two[i], two[j]);
			if(k)
				update(one[k-1], two[i], two[j]);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<ll> neg, pos;
	for(int i=0; i<n; i++) {
		ll t;
		cin >> t;
		if(t > 0) pos.push_back(t);
		else neg.push_back(t);
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
	int m = neg.size();
	if(m >= 3)
		update(neg[m-1], neg[m-2], neg[m-3]);
	if(pos.size() >= 3)
		update(pos[0], pos[1], pos[2]);
	f(neg, pos);
	f(pos, neg);
	cout << ansv[0] << ' ' << ansv[1] << ' ' << ansv[2];
}
