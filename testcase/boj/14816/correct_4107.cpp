#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[101][4][4][4], acc[101], cnt[4];
void smx(int &a, int b) {
	a = max(a, b);
}
int solve() {
	int n, p;
	cin >> n >> p;
	memset(cnt, 0, sizeof cnt);
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		t %= p;
		cnt[t]++;
		acc[i] = acc[i-1] + t;
	}
	if(p == 2) {
		return cnt[0] + (cnt[1]+1) / 2;
	} else if(p == 3) {
		int ans = cnt[0];
		int tmp = min(cnt[1], cnt[2]);
		ans += tmp;
		cnt[1] -= tmp;
		cnt[2] -= tmp;
		ans += cnt[1] / 3 + cnt[2] / 3 + (cnt[1] % 3 || cnt[2] % 3);
		return ans;
	} else {
		int ans = cnt[0];
		// 3-1
		int tmp = min(cnt[1], cnt[3]);
		ans += tmp;
		cnt[1] -= tmp;
		cnt[3] -= tmp;
		// 2-2
		ans += cnt[2] / 2;
		cnt[2] %= 2;
		// 2-1-1
		tmp = min(cnt[1]/2, cnt[2]);
		ans += tmp;
		cnt[1] -= tmp * 2;
		cnt[2] -= tmp;
		// 3-3-2
		tmp = min(cnt[3]/2, cnt[2]);
		ans += tmp;
		cnt[3] -= tmp * 2;
		cnt[2] -= tmp;
		// 1-1-1-1
		ans += cnt[1] / 4;
		cnt[1] %= 4;
		// 3-3-3-3
		ans += cnt[3] / 4;
		cnt[3] %= 4;
		return ans + (cnt[1] || cnt[2] || cnt[3]);
		// memset(dp, -1, sizeof dp);
		// dp[0][0][0][0] = 0;
		// for(int i=0; i<n; i++) {
		// 	for(int j=0; j<4; j++) {
		// 		for(int k=0; k<4; k++) {
		// 			for(int l=0; l<4; l++) {
		// 				if(dp[i][j][k][l] == -1)
		// 					continue;
		// 				int num = acc[i+1] - acc[i];
		// 				int val = dp[i][j][k][l];
		// 				if(num == 0) {
		// 					smx(dp[i+1][j][k][l], val + 1);
		// 				} else if(num == 1) {
		// 					if(j == 3)
		// 						smx(dp[i+1][0][k][l], val+1);
		// 					else
		// 						smx(dp[i+1][j+1][k][l], val);
		// 					if(k) {
		// 						if(l == 3) {
		// 							smx(dp[i+1][j][k-1][0], val+1);
		// 						} else {
		// 							smx(dp[i+1][j][k-1][l+1], val);
		// 						}
		// 					}
		// 					if(l)
		// 						smx(dp[i+1][j][k][l-1], val+1);
		// 				} else if(num == 2) {
		// 					if(k == 1)
		// 						smx(dp[i+1][j][0][l], val+1);
		// 					else
		// 						smx(dp[i+1][j][k+1][l], val);
		// 					if(j) {
		// 						if(l == 3) {
		// 							smx(dp[i+1][j-1][k][0], val+1);
		// 						} else {
		// 							smx(dp[i+1][j-1][k][l+1], val);
		// 						}
		// 					}
		// 					if(l) {
		// 						if(j == 3) {
		// 							smx(dp[i+1][0][k][l-1], val+1);
		// 						} else {
		// 							smx(dp[i+1][j+1][k][l-1], val);
		// 						}
		// 					}
		// 				} else if(num == 3) {
		// 					if(l == 3)
		// 						smx(dp[i+1][j][k][0], val+1);
		// 					else
		// 						smx(dp[i+1][j][k][l+1], val);
		// 					if(j)
		// 						smx(dp[i+1][j-1][k][l], val+1);
		// 					if(k) {
		// 						if(j == 3) {
		// 							smx(dp[i+1][0][k-1][l], val+1);
		// 						} else {
		// 							smx(dp[i+1][j+1][k-1][l], val);
		// 						}
		// 					}
		// 				}
		// 			}
		// 		}
		// 	}
		// }
		// int mx = 0;
		// for(int j=0; j<4; j++) {
		// 	for(int k=0; k<4; k++) {
		// 		for(int l=0; l<4; l++) {
		// 			mx = max(mx, dp[n][j][k][l] + (j || k || l));
		// 		}
		// 	}
		// }
		// return mx;
	}
}
int32_t main() {
	int t;
	cin >> t;
	for(int i=1; i<=t; i++) {
		printf("Case #%d: %d\n", i, solve());
	}
}
