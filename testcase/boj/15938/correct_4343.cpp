#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int dp[201][401][401];
bool cant[401][401];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int xs, ys, xh, yh, T;
	cin >> xs >> ys >> T >> xh >> yh;
	if(abs(xs-xh)+abs(ys-yh) > T)
		return !(cout << 0);
	int n;
	cin >> n;
	while(n--) {
		int x, y;
		cin >> x >> y;
		if(abs(x-xs)+abs(y-ys) <= T)
			cant[x-xs+200][y-ys+200] = true;
	}
	xh = xh - xs + 200;
	yh = yh - ys + 200;
	dp[0][200][200] = 1;
	int ans = 0;
	for(int t=1; t<=T; t++) {
		for(int i=0; i<=400; i++) {
			for(int j=0; j<=400; j++) {
				if(cant[i][j]) continue;
				if(i+1 <= 400)
					dp[t][i][j] = (dp[t][i][j] + dp[t-1][i+1][j]) % MOD;
				if(i-1>=0)
					dp[t][i][j] = (dp[t][i][j] + dp[t-1][i-1][j]) % MOD;
				if(j-1>=0)
					dp[t][i][j] = (dp[t][i][j] + dp[t-1][i][j-1]) % MOD;
				if(j+1<=400)
					dp[t][i][j] = (dp[t][i][j] + dp[t-1][i][j+1]) % MOD;
			}
		}
		ans = (ans + dp[t][xh][yh]) % MOD;
		dp[t][xh][yh] = 0;
	}
	cout << ans;
}
