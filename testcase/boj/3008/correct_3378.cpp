#include <bits/stdc++.h>
using namespace std;
struct Pt {
	int x, y;
	Pt operator-(Pt &p) {
		return {x-p.x, y-p.y};
	}
	void inv() {
		swap(x, y);
		x = -x;
	}
	void simp() {
		if(!x) y = 1;
		else if(!y) x = 1;
		else {
			int g = __gcd(x, y);
			x /= g;
			y /= g;
			if(y < 0) {
				x = -x;
				y = -y;
			}
		}
	}
	bool operator<(const Pt &p) const {
		return tie(x, y) < tie(p.x, p.y);
	}
};
const int MX = 1500;
Pt arr[MX];
vector<Pt> mp[MX];
int n;
int cnt(int i, Pt &p) {
	auto pr = equal_range(mp[i].begin(), mp[i].end(), p);
	return pr.second - pr.first;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
		mp[i].reserve(n-1);
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			if(i == j) continue;
			Pt v = arr[j]-arr[i];
			v.simp();
			mp[i].push_back(v);
			mp[j].push_back(v);
		}
	}
	for(int i=0; i<n; i++)
		sort(mp[i].begin(), mp[i].end());
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			Pt v = arr[j]-arr[i];
			v.inv();
			v.simp();
			ans += cnt(i, v) + cnt(j, v);
		}
	}
	assert(ans % 2 == 0);
	cout << ans / 2;
}
