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
	double a[n];
	rep(i,n) cin >> a[i];
	double ans = 0;
	for(int i=0; i<n; i++) {
		double temp = 1;
		for(int j=i; j<n; j++) {
			temp *= a[j];
			ans = max(ans, temp);
		}
	}
	cout << fixed << setprecision(3) << ans;
}
