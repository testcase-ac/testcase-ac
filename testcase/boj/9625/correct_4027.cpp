#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int dp[46][2] = {};
	dp[0][0] = 1;
	int K;
	cin >> K;
	for(int i=1; i<=K; i++) {
		dp[i][0] = dp[i-1][1];
		dp[i][1] = dp[i-1][0] + dp[i-1][1];
	}
	printf("%d %d", dp[K][0], dp[K][1]);
}
