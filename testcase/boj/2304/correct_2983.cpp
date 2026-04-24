#include <bits/stdc++.h>
using namespace std;
int arr[1001], mxsuf[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, mx = 0;
	cin >> n;
	for(int i=0; i<n; i++) {
		int l, h;
		cin >> l >> h;
		arr[l] = h;
		mx = max(mx, h);	
	}
	mxsuf[1000] = arr[1000];
	for(int i=999; i; i--)
		mxsuf[i] = max(mxsuf[i+1], arr[i]);
	int ans = 0, h = 0;
	for(int i=1; i<=1000; i++) {
		if(mxsuf[i] == mx)
			h = max(h, arr[i]);
		else
			h = mxsuf[i];
		ans += h;
	}
	cout << ans;
}
