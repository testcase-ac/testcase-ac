#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	double x, y, ans;
	cin >> x >> y;
	ans = x / y * 1000;
	int n;
	cin >> n;
	rep(i,n) {
		cin >> x >> y;
		ans = min(ans, x/y*1000);
	}
	cout << ans;
}
