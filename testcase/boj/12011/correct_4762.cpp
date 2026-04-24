#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
	int x, y;
	bool operator<(const point p) const {
		return tie(x, y) < tie(p.x, p.y);
	}
};
struct comp {
	bool operator()(const point a, const point b) const {
		return tie(a.y, a.x) < tie(b.y, b.x);
	}
};
const int MX = 5e4+2;
int n, mx;
point arr[MX];
int f() {
	set<point, comp> lft, rht;
	for(int i=0; i<n; i++) {
		rht.insert(arr[i]);
	}
	mx = (arr[n-1].x-arr[0].x)*(rht.rbegin()->y-rht.begin()->y);
	int ans = LLONG_MAX;
	for(int i=0, j=0; i<n; i=j) {
		while(j < n && arr[i].x == arr[j].x) {
			lft.insert(arr[j]);
			rht.erase(arr[j]);
			j++;
		}
		if(j == n) {
			return ans;
		}
		int c1 = (arr[i].x-arr[0].x)*(lft.rbegin()->y-lft.begin()->y);
		int c2 = (arr[n-1].x-arr[j].x)*(rht.rbegin()->y-rht.begin()->y);
		ans = min(ans, c1+c2);
	}
	exit(1);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
	}
	sort(arr, arr+n);
	int ans = f();
	for(int i=0; i<n; i++) {
		swap(arr[i].x, arr[i].y);
	}
	sort(arr, arr+n);
	ans = min(ans, f());
	cout << mx - ans;
}
