#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

inline ll seriessum(int l, int r, int d) { // assert((r-l)%d==0 && l <= r)
	return (l+r)*((r-l)/d+1)/2;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll ans = 0;
	int n;
	cin >> n;
	for(int i=0; i<=n; i++)
		ans += seriessum(i*2,i+n,1);
	cout << ans;
}
