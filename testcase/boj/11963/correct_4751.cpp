#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	set<int> st;
	for(int i=1; i<=2*n; i++) {
		st.insert(i);
	}
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
		st.erase(v[i]);
	}
	sort(v.begin(), v.begin()+n/2, greater<int>());
	int ans = 0;
	for(int i=0; i<n/2; i++) {
		if(v[i] < *st.rbegin()) {
			st.erase(prev(st.end()));
			ans++;
		}
	}
	for(int i=0; i<n/2-ans; i++) {
		st.erase(prev(st.end()));
	}
	sort(v.begin()+n/2, v.end());
	for(int i=n/2; i<n; i++) {
		if(v[i] > *st.begin()) {
			st.erase(st.begin());
			ans++;
		}
	}
	cout << ans;
}
