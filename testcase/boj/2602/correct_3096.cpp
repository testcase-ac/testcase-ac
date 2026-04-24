#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
string p, a[2];
int dp[21][101][2];
// dp[x][y][z]: ans when p = p[x:], a = a[y:], b = b[z:]
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> p >> a[0] >> a[1];
	rep(y, sz(a[0])+1) rep(i,2) dp[sz(p)][y][i] = 1;
	for(int x=sz(p)-1; x>=0; x--) {
		for(int y=sz(a[0])-1; y>=0; y--) {
			rep(i,2) {
				dp[x][y][i] = dp[x][y+1][i];
				if(p[x] == a[i][y])
					dp[x][y][i] += dp[x+1][y+1][!i];
			}
		}
	}
	cout << dp[0][0][0] + dp[0][0][1];
}
