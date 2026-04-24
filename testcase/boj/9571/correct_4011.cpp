#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5;
int rmx[MX], lmx[MX];
pair<int, int> arr[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, d;
	cin >> n >> d;
	for(int i=0; i<n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	sort(arr, arr+n);
	multiset<int> st;
	for(int i=0, j=0; i<n; i++) {
		while(arr[j].first < arr[i].first - d) {
			st.erase(st.find(arr[j++].second));
		}
		lmx[i] = (st.empty() ? 0ll : *st.rbegin());
		st.insert(arr[i].second);

	}
	st = {};
	for(int i=n-1, j=n-1; i>=0; i--) {
		while(arr[j].first > arr[i].first + d) {
			st.erase(st.find(arr[j--].second));
		}
		rmx[i] = (st.empty() ? 0ll : *st.rbegin());
		st.insert(arr[i].second);
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		if(lmx[i] >= arr[i].second * 2 && rmx[i] >= arr[i].second * 2) {
			ans++;
		}
	}
	cout << ans;
}
