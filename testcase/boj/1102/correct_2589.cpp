#include <bits/stdc++.h>
using namespace std;
int cost[16][16];
int dp[1<<16];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, p;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> cost[i][j];
		}
	}
	for(int i=0; i<(1<<n); i++) {
		dp[i] = INT_MAX;
	}
	string st;
	cin >> st >> p;
	int init = 0, cnt = 0;
	for(int i=0; i<n; i++) {
		if(st[i] == 'Y') {
			init += (1 << i);
			cnt++;
		}
	}
	if(cnt >= p) return !(cout << 0);
	if(!cnt) return !(cout << -1);
	dp[init] = 0;
	p -= cnt;
	queue<int> que;
	que.push(init);
	int ans = 0;
	//printf("p = %d\n", p);
	while(p--) {
		ans = INT_MAX;
		int s = (int)que.size();
		while(s--) {
			int bm = que.front();
			que.pop();
			vector<int> onv, nov;
			for(int i=0; i<n; i++) {
				if(bm & (1 << i)) onv.push_back(i);
				else nov.push_back(i);
			}
			for(int i: nov) {
				int mc = 100;
				for(int j: onv)
					mc = min(mc, cost[j][i]);
				int newbm = bm | (1 << i);
				bool push = (dp[newbm] == INT_MAX);
				dp[newbm] = min(dp[newbm], dp[bm] + mc);
				//printf("p=%d, bm=%d, newbm=%d, mc=%d\n", p, bm, newbm, mc);
				ans = min(ans, dp[newbm]);
				if(push) que.push(newbm);
			}
		}
	}
	cout << ans;
}
