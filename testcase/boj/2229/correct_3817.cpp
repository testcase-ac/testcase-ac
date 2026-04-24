#include <bits/stdc++.h>
using namespace std;

int arr[1000], dp[1000];

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(int i=1; i<n; i++) {
		int mn = arr[i], mx = arr[i];
		for(int j=i; j>=0; j--) {
			mn = min(mn, arr[j]), mx = max(mx, arr[j]);
			dp[i] = max(dp[i], j?dp[j-1]+(mx-mn):(mx-mn));
		}
	}
	cout << dp[n-1];
}
