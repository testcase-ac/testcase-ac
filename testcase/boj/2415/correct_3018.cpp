#include <bits/stdc++.h>
using namespace std;
#define int long long
int dot(int a, int b, int x, int y) {
	return a*x + b*y;
}
struct vec {
	int x, y, dx, dy;
	vec(int x1, int y1, int x2, int y2) {
		if(x1 > x2 || (x1 == x2 && y1 > y2)) {
			swap(x1, x2);
			swap(y1, y2);
		}
		x = x1, y = y1, dx = x2 - x1, dy = y2 - y1;
	}

	bool operator<(const vec& v) const {
		if(tie(dx, dy) != tie(v.dx, v.dy)) {
			return tie(dx, dy) < tie(v.dx, v.dy);
		}
		return dot(dx, dy, x, y) < dot(dx, dy, v.x, v.y);
	}
	bool operator==(const vec& v) const {
		return tie(dx, dy) == tie(v.dx, v.dy) && dot(dx, dy, x, y) == dot(dx, dy, v.x, v.y);
	}
};
int sq(int t){
	return t*t;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<vec> v;
	vector<pair<int, int>> arr(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			v.emplace_back(arr[i].first, arr[i].second, arr[j].first, arr[j].second);
		}
	}
	sort(v.begin(), v.end());
	int ans = 0;
	for(int i=0, j=0; i<v.size(); i=j) {
		while(j < v.size() && v[i] == v[j])
			j++;
		if(i+1 == j) continue;
		auto res = minmax_element(v.begin()+i, v.begin()+j, [](auto a, auto b){
			return tie(a.x, a.y) < tie(b.x, b.y);
		});

		ans = max(ans, (int)(sqrt(sq(res.first->x-res.second->x) + sq(res.first->y-res.second->y)) * sqrt(sq(res.first->dx) + sq(res.first->dy))));
	}
	cout << ans;
}
