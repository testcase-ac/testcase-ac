#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	pair<int, int> arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i].second >> arr[i].first;
	}
	sort(arr, arr+n);
	int a[n], dp[n], m = 0;
	for(int i=0; i<n; i++) {
		a[i] = arr[i].second;
		m = max(m, a[i]);
	}
	int pref[m+1];
	memset(dp, 0x3f, sizeof dp);
	memset(pref, -1, sizeof pref);
	int maxp = 0;
	set<int> st(a, a+n);
	for(int i=0; i<n; i++) {
		int p = upper_bound(dp, dp+n, a[i]) - dp;
		dp[p] = a[i];
		if(p)
			pref[a[i]] = dp[p-1];
		maxp = max(p,maxp);
	}
	int t = dp[maxp];
	while(t != -1) {
		st.erase(t);
		t = pref[t];
	}
	cout << st.size() << '\n';
	for(int i: st) {
		cout << i << '\n';
	}
}
