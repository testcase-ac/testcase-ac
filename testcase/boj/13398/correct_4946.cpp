#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[n], end[n] = {}, start[n] = {};
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	int ans = INT_MIN, curr = 0;
	for(int i=0; i<n; i++) {
		curr = curr+a[i];
		ans = max(curr,ans);
		curr = max(curr, 0);
	}
	end[0] = a[0];
	for(int i=1; i<n; i++)
		end[i] = max(a[i],end[i-1]+a[i]);

	start[n-1] = a[n-1];
	for(int i=n-2; i>=0; i--)
		start[i] = max(a[i],start[i+1]+a[i]);

	for(int i=0; i<n-2; i++) {
		ans = max(ans, end[i] + start[i+2]);
	}
	cout << ans;
}
