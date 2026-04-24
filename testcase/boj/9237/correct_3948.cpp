#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0;
	cin >> n;
	int arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n, greater<int>());
	for(int i=0; i<n; i++) {
		ans = max(ans,arr[i]+i+1);
	}
	cout << ans+1;
}
