#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int n;
int solve(int *a) {
	int temp = 1, ans = 1;
	for(int i=1; i<n; i++) {
		if(a[i-1] <= a[i])
			temp++;
		else
			temp = 1;
		ans = max(temp, ans);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	int a[n];
	rep(i,n) cin >> a[i];
	int ans = solve(a);
	reverse(a, a+n);
	ans = max(ans, solve(a));
	cout << ans;
}
