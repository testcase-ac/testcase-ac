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
	int n, s;
	cin >> n >> s;
	if(n == 1) {
		int t;
		cin >> t;
		return !(cout << (t==s));
	}
	int n1 = n/2, n2 = n - n1;
	int a1[n1], a2[n2];
	rep(i,n1) cin >> a1[i];
	rep(i,n2) cin >> a2[i];
	vector<int> possible(1<<n2);
	ll ans = 0;
	possible[0] = 0;
	for(int i=1; i<(1<<n2); i++) {
		rep(j,n2)
			if(i & (1 << j)) possible[i] += a2[j];
		if(possible[i] == s) ans++;
	}
	sort(possible.begin(), possible.end());
	for(int i=1; i<(1<<n1); i++) {
		int sum = 0;
		rep(j,n1)
			if(i & (1 << j)) sum += a1[j];
		auto pr = equal_range(possible.begin(), possible.end(), s-sum);
		ans += (pr.second - pr.first);
	}
	cout << ans;
}
