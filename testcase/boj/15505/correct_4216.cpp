#include <bits/stdc++.h>
using namespace std;
const int MX = 20;
int dp[10][1<<MX], cnt[10][1<<MX], vals[4][10][10], n, m, tdp[1<<MX], tcnt[1<<MX];
const int MOD = 1e9+7;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int t=0; t<4; t++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				cin >> vals[t][i][j];
			}
		}
	}
	memset(dp, 0xbf, sizeof dp);
	for(int i=0; i<4; i++) {
		dp[0][i<<(2*(m-1))] = vals[i][0][0];
		cnt[0][i<<(2*(m-1))] = 1;
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(!i && !j) continue;
			int shift = 2*(m-1-j);
			memset(tdp, 0xbf, sizeof tdp);
			for(int bm=0; bm<(1<<MX); bm++) {
				int t = (bm >> shift) & 3, pt = j ? ((bm >> (shift + 2)) & 3) : -1;
				if(t == pt) continue;
				for(int nt=0; nt<4; nt++) {
					if(i && (nt == t)) continue;
					int nbm = (bm ^ (t << shift)) ^ (nt << shift);
					int v = dp[(j+m-1) % m][nbm] + vals[t][i][j];
					if(v < 0)
						continue;
					if(v > tdp[bm]) {
						tdp[bm] = v;
						tcnt[bm] = cnt[(j+m-1) % m][nbm];
						//printf("at i=%d, j=%d, dp replaced to %d at bm=%d. now cnt is %d\n", i, j, v, bm, tcnt[bm]);
					} else if(v == tdp[bm]) {
						tcnt[bm] += cnt[(j+m-1) % m][nbm];
						tcnt[bm] %= MOD;
						//printf("at i=%d, j=%d, dp same to %d at bm=%d. now cnt is %d\n", i, j, v, bm, tcnt[bm]);
					}
				}
			}
			memcpy(dp[j], tdp, sizeof tdp);
			memcpy(cnt[j], tcnt, sizeof tcnt);
		}
	}
	int i = max_element(dp[m-1], dp[m-1]+(1<<MX)) - dp[m-1];
	int k = 0;
	for(int j=0; j<(1<<MX); j++) {
		if(dp[m-1][j] == dp[m-1][i] && cnt[m-1][j]) {
			//printf("last, equal at %d. accumulate %d\n", j, cnt[m-1][j]);
			k += cnt[m-1][j];
			k %= MOD;
		}
	}
	cout << dp[m-1][i] << ' ' << k;
}
