#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

string a, b, c;

int dp[101][101][101];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> a >> b >> c;
	for(int i=1; i<=sz(a); i++) {
		for(int j=1; j<=sz(b); j++) {
			for(int k=1; k<=sz(c); k++) {
				if(a[i-1] == b[j-1] && b[j-1] == c[k-1]) dp[i][j][k] = dp[i-1][j-1][k-1]+1;
				else dp[i][j][k] = max({dp[i-1][j][k], dp[i][j-1][k], dp[i][j][k-1]});
			}
		}
	}
	cout << dp[sz(a)][sz(b)][sz(c)];
}
