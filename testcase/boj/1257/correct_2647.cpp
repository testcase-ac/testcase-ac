#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 10001;
int dp[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m, n;
	cin >> m >> n;
	vector<int> w(n);
	for(int i=0; i<n; i++) {
		cin >> w[i];
	}
	sort(w.begin(), w.end(), greater<int>());
	memset(dp, 0x3f, sizeof dp);
	dp[0] = m / w[0];
	deque<int> que;
	que.push_back(0);
	while(que.size()) {
		int q = que.front();
		que.pop_front();
		for(int t: w) {
			int v, g;
			if(q+t >= w[0]) {
				v = q+t-w[0], g = 0;
			} else {
				v = q+t, g = 1;
			}
			if(dp[q] + g < dp[v]) {
				dp[v] = dp[q]+g;
				if(g == 0) {
					que.push_front(v);
				} else {
					que.push_back(v);
				}
			}
		}
	}
	cout << dp[m % w[0]];
}
