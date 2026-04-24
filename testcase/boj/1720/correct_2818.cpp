#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;
/*
dp[n] - (1 for i in dp[n/2] if rev(i) != i)
*/
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	if(n == 1) return !(cout << 1);
	ll dp[n+1];
	dp[0] = dp[1] = 1;
	for(int i=2; i<=n; i++)
		dp[i] = dp[i-2]*2 + dp[i-1];
	cout << (dp[n]+(n&1? dp[n/2] : dp[n/2]+2*dp[n/2-1]))/2;
}
