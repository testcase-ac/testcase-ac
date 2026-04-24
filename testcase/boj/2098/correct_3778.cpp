#include <iostream>

#define MOD 1000000007
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
#define MAXN 16
int n;
pair<int,int> dp[1<<MAXN][MAXN];
/*
dp[bitmask][x]:
	(the minimum dist of traversing each of bitmasked node *once* starting from x,
	the end of such minimum-dist path)
*/
int dist[MAXN][MAXN];
inline bool isPowerOf2(int x) {
	return x && !(x & (x - 1));
}

pair<int,int> solve(int bitmask, int x) {
	if(dp[bitmask][x].second != -1 ) {  // memoized
		return dp[bitmask][x];
	}
	if(isPowerOf2(bitmask)) {  // base case(1 node to traverse)
		dp[bitmask][x].first = 0;
		dp[bitmask][x].second = x;
		return dp[bitmask][x];
	}
	dp[bitmask][x] = {MOD, x};
	int nextbm = bitmask ^ (1 << x);
	rep(i, n) { // x -> i -> ... -> end(dp[bitmask][i].second)
		if(nextbm & (1<<i) && dist[x][i]) {
			auto pr = solve(nextbm, i);
			if(dp[bitmask][x].first > dist[x][i] + pr.first) { 
				dp[bitmask][x].first = dist[x][i] + pr.first;
				dp[bitmask][x].second = pr.second;
			}
		}
	}
	return dp[bitmask][x];
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	rep(i, n) rep(j, n) cin >> dist[i][j];
	rep(i, 1<<n) rep(j, n) dp[i][j].second = -1;
	int ans = MOD;
	rep(i, n) {
		auto pr = solve((1<<n)-1, i);
		if(dist[pr.second][i])
			ans = min(ans, pr.first+dist[pr.second][i]);
	}
	cout << ans;
}