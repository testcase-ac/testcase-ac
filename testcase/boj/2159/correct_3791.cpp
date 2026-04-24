#include <bits/stdc++.h>
using namespace std;
int dist(pair<int, int> a, pair<int, int> b) {
	return abs(a.first-b.first)+abs(a.second-b.second);
}
typedef long long ll;
const int MX = 1e5+3;
int dx[] = {1,-1,0,0,0}, dy[] = {0,0,1,-1,0};
ll dp[MX][5];
pair<int, int> pos[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> pos[0].first >> pos[0].second;
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 1;
	dp[0][4] = 0;
	for(int i=1; i<=n; i++) {
		cin >> pos[i].first >> pos[i].second;
		for(int a=0; a<5; a++) {
			for(int b=0; b<5; b++) {
				if(dp[i-1][a]+dist({pos[i-1].first+dx[a], pos[i-1].second+dy[a]}, {pos[i].first+dx[b], pos[i].second+dy[b]}) < dp[i][b])
					dp[i][b] = dp[i-1][a]+dist({pos[i-1].first+dx[a], pos[i-1].second+dy[a]}, {pos[i].first+dx[b], pos[i].second+dy[b]});
			}
		}
	}
	cout << *min_element(dp[n], dp[n]+5);
}
