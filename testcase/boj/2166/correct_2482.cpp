#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll cross(pair<ll, ll> a, pair<ll, ll> b) {
	return a.first * b.second - a.second * b.first;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pair<ll, ll>> pt(n);
	for(int i=0; i<n; i++) {
		cin >> pt[i].first >> pt[i].second;
	}
	ll ans = 0;
	for(int i=0; i<n-1; i++) {
		ans += cross(pt[i+1], pt[i]);
	}
	ans += cross(pt[0], pt[n-1]);
	double a = (double)ans/2;
	if(a < 0) a = -a;
	cout << fixed << setprecision(1) << a;
}
