#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int& x : a) cin >> x;
	vector<int> pmin = a, smin = a;
	for(int i = 1; i < n; i++) pmin[i] = min(pmin[i-1], pmin[i]);
	for(int i = n-1; i > 0; i--) smin[i-1] = min(smin[i-1], smin[i]);
	int ans = smin[0];
	for(int i = 1; i < n; i++){
		ans = max(ans, min(pmin[i-1] + (n-i)*k, smin[i] - (i*k)));
	}
	cout << ans << '\n';
}
