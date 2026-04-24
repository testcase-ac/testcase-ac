#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	pair<int, int> arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	sort(arr, arr+n);
	int i = 0, ans = 0;
	while(i<n) {
		int l = arr[i].first, r = arr[i].second;
		i++;
		while(i<n) {
			if(l <= arr[i].first && arr[i].first <= r) {
				r = max(r, arr[i].second);
				i++;
			} else break;
		}
		ans += (r-l);
	}
	cout << ans;
}
