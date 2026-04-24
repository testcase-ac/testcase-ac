#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

ll dp[101][101][101];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
  	int N, L, R;
	cin >> N >> L >> R;
	dp[1][1][1] = 1;
	for(int n=2; n<=N; n++) {
		for(int l=1; l<=n; l++) {
			for(int r=1; r<=n; r++) {
				dp[n][l][r] = (dp[n-1][l-1][r] + dp[n-1][l][r-1] + dp[n-1][l][r]*(n-2));
			}
		}
	}
	cout << dp[N][L][R] << '\n';      
    }

}
