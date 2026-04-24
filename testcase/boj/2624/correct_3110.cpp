#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int dp[100][10001];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	int coin[k], cnts[k];
	rep(i,k) cin >> coin[i] >> cnts[i];
	for(int i=0; i<=cnts[0]; i++) {
		int v = i*coin[0];
		if(v > n) break;
		dp[0][v] = 1;
	}
	for(int c=1; c<k; c++) {
		for(int i=0; i<=n; i++) {
			if(!dp[c-1][i]) continue;
			for(int j=0; j<=cnts[c]; j++) {
				int v = i+j*coin[c];
				if(v > n) break;
				dp[c][v] += dp[c-1][i];
			}
		}
	}
	cout << dp[k-1][n];
}
