#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 2e9;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), dp(n), ind(n), prv(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	fill(dp.begin(), dp.end(), INF);
	int ans = 0;
	for(int i=0; i<n; i++) {
		int lb = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
		dp[lb] = a[i];
		ind[lb] = i;
		ans = max(ans, lb);
		if(lb)
			prv[i] = ind[lb-1];
	}
	cout << ans+1 << '\n';
	vector<int> v;
	int c = ind[ans];
	for(int i=0; i<=ans; i++) {
		v.push_back(a[c]);
		c = prv[c];
	}
	reverse(v.begin(), v.end());
	for(int i: v) cout << i << ' ';
}
