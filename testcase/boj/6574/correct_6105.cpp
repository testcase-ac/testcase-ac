#include <bits/stdc++.h>
using namespace std;
#define int long long
char a[200], b[200];
int dp[200][200], prv[200][200];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while((cin >> (a+1) >> (b+1)).good()) {
		int n = strlen(a+1), m = strlen(b+1);
		memset(dp, 0x3f, sizeof dp);
		dp[0][0] = 0;
		for(int i=1; i<200; i++) {
			dp[i][0] = dp[0][i] = i;
		}
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				if(a[i] == b[j]) {
					dp[i][j] = dp[i-1][j-1] + 1;
				}
				dp[i][j] = min({dp[i][j], dp[i][j-1]+1, dp[i-1][j]+1});
			}
		}
		int i = n, j = m;
		string ans;
		while(i > 0 || j > 0) {
			if(a[i] == b[j]) {
				ans.push_back(a[i]);
				i--;
				j--;
			} else {
				bool use_b = false;
				if(!i || !j) {
					if(!i)
						use_b = true;
				} else {
					if(dp[i][j-1] < dp[i-1][j]) 
						use_b = 1;
				}
				if(use_b) {
					ans.push_back(b[j]);
					j--;
				} else {
					ans.push_back(a[i]);
					i--;
				}
			}
		}
		reverse(ans.begin(), ans.end());
		cout << ans << '\n';
	}
}
