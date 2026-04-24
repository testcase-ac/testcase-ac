#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s1, s2;
	cin >> s1 >> s2;
	int ans = 0;
	int dp[sz(s1)+1][sz(s2)+1];
	set0(dp);
	for(int i=1; i<=sz(s1); i++) {
		for(int j=1; j<=sz(s2); j++) {
			if(s1[i-1] == s2[j-1]) {
				dp[i][j] = dp[i-1][j-1]+1;
				ans = max(ans, dp[i][j]);
			}
		}
	}
	cout << ans;
}
