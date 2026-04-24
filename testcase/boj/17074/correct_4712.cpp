#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+5;
int a[MX], pre[MX], suf[MX];

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	pre[0] = suf[n+1] = 1;
	a[0] = INT_MIN;
	a[n+1] = INT_MAX; 
	for(int i=1; i<=n; i++) {
		if(a[i-1] <= a[i])
			pre[i] = 1;
		else break;
	}
	for(int i=n; i>=1; i--) {
		if(a[i] <= a[i+1])
			suf[i] = 1;
		else break;
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		if(pre[i-1] && suf[i+1] && a[i-1] <= a[i+1]) {
			ans++;
		}
	}
	cout << ans;
}
