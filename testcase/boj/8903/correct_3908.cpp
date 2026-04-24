#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[10000][5], dp[32];
int solve() {
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n; i++) {
		for(int j=0; j<5; j++) {
			cin >> arr[i][j];
		}
	}
	memset(dp, 0, sizeof dp);
	for(int i=0; i<n; i++) {
		for(int bm=1; bm<32; bm++) {
			int sum = 0;
			for(int j=0; j<5; j++) {
				if(bm&(1<<j))
					sum += arr[i][j];
			}
			dp[bm] = max(dp[bm], sum);
		}
	}
	if(k >= 5)
		return dp[1] + dp[2] + dp[4] + dp[8] + dp[16];
	if(k == 1)
		return dp[31];
	if(k == 2) {
		int ans = 0;
		for(int i=1; i<32; i++) {
			for(int j=1; j<32; j++) {
				if(i & j) continue;
				if((i | j) != 31) continue;
				ans = max(ans, dp[i]+dp[j]);
			}
		}
		return ans;
	}
	if(k == 3) {
		int ans = 0;
		for(int i=1; i<32; i++) {
			for(int j=1; j<32; j++) {
				for(int l=1; l<32; l++) {
					if(i&j) continue;
					if(j&l) continue;
					if(i&l) continue;
					if((i | j | l) != 31) continue;
					ans = max(ans, dp[i]+dp[j]+dp[l]);
				}
			}
		}
		return ans;
	}
	if(k == 4) {
		int ans = 0;
		for(int i=1; i<32; i++) {
			for(int j=1; j<32; j++) {
				for(int l=1; l<32; l++) {
					for(int t=1; t<32; t++) {
						if(i&j) continue;
						if(i&l) continue;
						if(i&t) continue;
						if(j&l) continue;
						if(j&t) continue;
						if(l&t) continue;
						if((i | j | l | t) != 31) continue;
						ans = max(ans, dp[i]+dp[j]+dp[l]+dp[t]);
					}
				}
			}
		}
		return ans;
	}
	throw "hi";
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		cout << solve() << '\n';
}
