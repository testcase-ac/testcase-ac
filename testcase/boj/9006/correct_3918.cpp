#include <bits/stdc++.h>
using namespace std;
#define int long long
double solve() {
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> arr;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		arr.push_back({t, m});
	}
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		arr.push_back({t, n});
	}
	sort(arr.begin(), arr.end());
	int s = -m*n*2;
	for(auto &pr: arr) {
		s += pr.second*2;
		//printf("at pos=%d, s = %d\n", pr.first, s);
		if(s >= 0) {
			return pr.first;
		}
	}
	return -1;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		cout << fixed << setprecision(1) << solve() << '\n';
}
