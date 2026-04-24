#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	ll a[n], acc = 0, ans = 0;
	for(int i=0; i<n; i++) {
		cin >> a[i];
		acc += a[i];
		if(i >= m)
			acc -= a[i-m];
		ans = max(ans, acc);
	}
	cout << ans;
}
