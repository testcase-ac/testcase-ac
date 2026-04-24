#include <bits/stdc++.h>
using namespace std;
int dp[100001];
queue<int> que;
void chk(vector<int> pos, int t) {
	for(int p: pos) {
		if(p < 0 || p > 100000 || dp[p] != -1) continue;
		que.push(p);
		dp[p] = t+1;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b, n, m;
	cin >> a >> b >> n >> m;
	memset(dp, -1, sizeof dp);
	dp[n] = 0;
	que.push(n);
	while(!que.empty()) {
		int t = que.front();
		que.pop();
		chk({t-1, t+1, t+a, t-a, t+b, t-b, t*a, t*b}, dp[t]);
	}
	cout << dp[m];
}
