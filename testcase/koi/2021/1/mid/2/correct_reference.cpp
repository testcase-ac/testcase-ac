#include <bits/stdc++.h>
using namespace std;

// KOI 2021 Preliminary
// '두 개의 팀' (Two teams) Model solution
// Author: Junwon Kim

// Time complexity: O(N)
// dp[x][0] : Maximum sum of weights with root x
// dp[x][1] : Maximum sum of weights EXCLUDING MINIMAL SELECTED NODES IN dp[x][0]
// dp[x][2] : Maximum dp[y][0] where y is in subtree rooted at x

using lint = long long;

const lint inf = 500000000000000ll;

int N, o, a[200004], p[200004];
lint dp[200004][3];
vector<int> ch[200004];

void dfs(int x) {

	dp[x][0] = dp[x][2] = a[x];
	dp[x][1] = -inf;

	for (int y : ch[x]) {
		dfs(y);

		if (dp[y][0] > 0) {
			dp[x][0] += dp[y][0];
			dp[x][1] = max(dp[x][1], dp[y][1]);
		} else {
			dp[x][1] = max(dp[x][1], dp[y][2]);
		}

		dp[x][2] = max(dp[x][2], dp[y][2]);
	}

	dp[x][2] = max(dp[x][0], dp[x][2]);
}

int main() {
	cin >> N;
	for (int x=1; x<=N; x++) {
		cin >> a[x] >> p[x];

		if (p[x] == -1) o = x;
		else ch[p[x]].push_back(x);
	}

	dfs(o);

	lint ans = -inf;

	for (int x=1; x<=N; x++) {
		ans = max(ans, dp[x][0] + dp[x][1]);

		vector<lint> v;
		for (int y : ch[x]) v.push_back(dp[y][2]);

		sort(v.begin(), v.end());
		reverse(v.begin(), v.end());

		if (v.size() >= 2) ans = max(ans, v[0] + v[1]);
	}

	assert(ans >= -inf / 2);
	cout << ans << '\n';
}