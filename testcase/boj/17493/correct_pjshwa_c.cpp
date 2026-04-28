#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

#define pb push_back
#define mp make_pair

const int MAXN = 200010;

vector<int> ed[MAXN];
int dp[MAXN][3];

void dfs(int x, int p) {
	dp[x][0] = 1;
	int mn = 1;
	for(auto a : ed[x]) if(a != p) {
		dfs(a, x);
		dp[x][0] += dp[a][2];
		dp[x][1] += dp[a][1];
		mn = min(mn, dp[a][0] - dp[a][1]);
		dp[x][2] += dp[a][1];
	}
	dp[x][1] = min(dp[x][0], dp[x][1] + mn);
	dp[x][2] = min(dp[x][2], dp[x][0]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M;

	cin >> N >> M;
	for(int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		ed[a].pb(b);
		ed[b].pb(a);
	}

	int ans = 0;
	for(int i = 1; i <= N; i++) if(!dp[i][0]) {
		dfs(i, 0);
		ans += dp[i][1];
	}

	//for(int i = 1; i <= N; i++) printf("%d %d %d\n", dp[i][0], dp[i][1], dp[i][2]);

	cout << ans;
	return 0;
}
