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
	int ans = arr[0].first + arr[n-1].first;
	for(int i=0; i<n/2+1; i++) {
		if(!binary_search(arr, arr+n, make_pair(ans-arr[i].first, arr[i].second)))
			return !(cout << "NO\n");
	}
	if(ans&1) printf("%d.5", (ans-1)/2);
	else printf("%d\n", ans/2);
}