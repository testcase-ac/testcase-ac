#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int e, f, c;
	cin >> e >> f >> c;
	e += f;
	int ans = 0;
	while(e >= c) {
		ans += e / c;
		e = e % c + e / c;
	}
	cout << ans;
}
