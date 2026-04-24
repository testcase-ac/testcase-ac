#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct line {
	ll a, b;
	double x;
	bool operator<(line l) {
		return x < l.x;
	}
	double intersect(line l) {
		return ((double)(l.b-b))/(a-l.a);
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	if(n == 1)
		return !(cout << 0);
	vector<ll> a(n), b(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		cin >> b[i];
	}
	vector<line> v;
	v.push_back({b[0], 0, 0});
	for(int i=1; i<n; i++) {
		line tmp = {b[i],-1,a[i]};
		int t = lower_bound(v.begin(), v.end(), tmp) - v.begin();
		t--;
		ll eval = v[t].a*a[i]+v[t].b;
		tmp.b = eval;
		if(i == n-1)
			return !(cout << eval);
		while(v.back().intersect(tmp) < v.back().x) {
			v.pop_back();
		}
		tmp.x = v.back().intersect(tmp);
		v.push_back(tmp);
	}
}
