#include <bits/stdc++.h>
using namespace std;
struct point {
	int x, y, p, i;
};
vector<point> buk[1001];
int dp[1001], ans, used[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<point> arr(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y >> arr[i].p;
		arr[i].i = i;
		buk[arr[i].x].push_back(arr[i]);
	}
	sort(arr.begin(), arr.end(), [](point a, point b){return a.y < b.y;});
	int h = 1, j = 0;
	auto calc = [&](int a, int b) {
		int cnt = 0;
		for(int i=0; i<n; i++) {
			if(arr[i].x <= a || arr[i].y <= b)
				cnt++;
		}
		ans = max(ans, cnt);
	};
	for(int i=1; i<=1000; i++) {
		for(auto p: buk[i]) {
			if(!used[p.i]) {
				h += p.p;
				used[p.i] = 1;
			}
		}
		while(j < n && arr[j].y <= h) {
			if(!used[arr[j].i]) {
				h += arr[j].p;
				used[arr[j].i] = 1;
			}
			j++;
		}
		calc(i, h);
		while(j && arr[j-1].y >= h) {
			if(arr[j-1].x > i) {
				h -= arr[j-1].p;
				used[arr[j-1].i] = 0;
			}
			j--;
		}
		h--;
		if(h <= 0) break;
	}
	cout << ans;
}
