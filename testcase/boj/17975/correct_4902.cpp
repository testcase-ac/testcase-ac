#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int lmx, rmx, mx, sum;
};
node combine(node l, node r) {
	node ret;
	ret.mx = max({l.mx, r.mx, l.rmx + r.lmx});
	ret.lmx = max(l.lmx, l.sum+r.lmx);
	ret.rmx = max(r.rmx, r.sum+l.rmx);
	ret.sum = l.sum + r.sum;
	return ret;
};
struct pt {
	int x, y, w;
};
const int MX = 4096;
node seg[MX*2];
void update(int i, int t) {
	i += MX;
	int v = seg[i].mx + t;
	seg[i].lmx = seg[i].rmx = seg[i].mx = seg[i].sum = v;
	while(i /= 2)
		seg[i] = combine(seg[i*2], seg[i*2+1]);
}

vector<pair<int, int>> buk[MX];
pt arr[MX];
int n;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int x, y;
	cin >> x;
	vector<pair<int, int>> p1(x);
	for(int i=0; i<x; i++) {
		cin >> p1[i].first >> p1[i].second;
	}
	cin >> y;
	vector<pair<int, int>> p2(y);
	for(int i=0; i<y; i++) {
		cin >> p2[i].first >> p2[i].second;
	}
	int s, b;
	cin >> s >> b;
	for(int i=0; i<x; i++) {
		arr[n++] = {p1[i].first, p1[i].second, s};
	}
	for(int i=0; i<y; i++) {
		arr[n++] = {p2[i].first, p2[i].second, -b};
	}
	vector<int> vx, vy;
	for(int i=0; i<n; i++) {
		vx.push_back(arr[i].x);
		vy.push_back(arr[i].y);
	}
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	sort(vy.begin(), vy.end());
	vy.erase(unique(vy.begin(), vy.end()), vy.end());
	for(int i=0; i<n; i++) {
		arr[i].x = lower_bound(vx.begin(), vx.end(), arr[i].x) - vx.begin();
		arr[i].y = lower_bound(vy.begin(), vy.end(), arr[i].y) - vy.begin();
		buk[arr[i].x].push_back({arr[i].y, arr[i].w});
	}
	int ans = 0;
	for(int i=0; i<vx.size(); i++) {
		memset(seg, 0, sizeof seg);
		for(int j=i; j<vx.size(); j++) {
			for(auto [y, w]: buk[j]) {
				update(y, w);
			}
			ans = max(ans, seg[1].mx);
		}
	}
	cout << ans;
}
