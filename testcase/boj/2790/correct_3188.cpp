#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n, greater<int>());
	multiset<int> st;
	for(int i=0; i<n; i++) {
		st.insert(a[i]+i+1);		
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		st.erase(st.find(a[i]+i+1));
		if(*st.rbegin() <= a[i]+n)
			ans++;
		else break;
		st.insert(a[i]+i+1);
	}
	cout << ans;
}
