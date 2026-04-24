#include <bits/stdc++.h>
using namespace std;
int getpi(string &p) {
	int n = p.size(), ret = 0;
	vector<int> pi(n);
	int j = 0;
	for(int i=1; i<n; i++) {
		while(j && p[j] != p[i])
			j = pi[j-1];
		if(p[j] == p[i])
			j++;
		pi[i] = j;
		ret = max(ret, pi[i]);
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	int ans = 0;
	while(s.size()) {
		ans = max(ans, getpi(s));
		s = s.substr(1);
	}
	cout << ans;
}
