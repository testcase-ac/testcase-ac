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
	int n;
	cin >> n;
	long double ans = 0;
	long double running = 1;
	rep(i,n) {
		double x;
		cin >> x;
		running *= x;
		ans = max(ans, running);
		if(running < 1) running = 1;
	}
	cout << fixed << setprecision(3) << ans;
}
