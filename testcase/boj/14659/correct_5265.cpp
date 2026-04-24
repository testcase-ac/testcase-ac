#include <bits/stdc++.h>
using namespace std;
int n, ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	int arr[n], ind[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		ind[i] = i;
	}
	sort(ind, ind+n, [&](int i, int j){return arr[i]>arr[j];});
	set<int> st;
	for(int t: ind) {
		auto it = st.lower_bound(t);
		ans = max(ans, (it == st.end() ? n : *it)-t-1);
		st.insert(t);
	}
	cout << ans;
}
