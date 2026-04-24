#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	vector<int> ans;
	for(int i=0; i<n; i++) {
		sort(v.begin(), v.end());
		set<int> st(v.begin(), v.end());
		if(st.size() != 2) {
			if(ans.empty() || ans.back()+1 != v[0]) {
				ans.push_back(v[0]);
				v.erase(v.begin());
			} else {
				ans.push_back(*next(st.begin()));
				v.erase(find(v.begin(), v.end(), *next(st.begin())));
			}
		} else {
			if((*st.begin()) + 1 == *st.rbegin() || (ans.size() && ans.back()+1 == *(st.begin()))) {
				ans.push_back(v.back());
				v.erase(v.end()-1);
			} else {
				ans.push_back(v[0]);
				v.erase(v.begin());
			}
		}
	}
	for(int a: ans)
		cout << a << ' ';
}
