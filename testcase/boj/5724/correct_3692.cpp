#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll dp[101];
	dp[1] = 1;
	for(int i=2; i<=100; i++) {
		dp[i] = dp[i-1] + (i*i);
	}
	int t;
	cin >> t;
	while(t) {
		cout << dp[t] << '\n';
		cin >> t;
	}

}
