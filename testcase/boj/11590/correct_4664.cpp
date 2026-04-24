#include <bits/stdc++.h>
using namespace std;
const int MX = 2e6+2;
vector<pair<int, int>> trie[MX];
int dp[MX], nxt = 1;
int trie_nxt(int cur, int ch) {
	for(auto &pr: trie[cur]) {
		if(pr.first == ch) {
			return pr.second;
		}
	}
	trie[cur].push_back({ch, nxt});
	cur = nxt;
	nxt++;
	return cur;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string s;
	int ans = 0;
	for(int t=0; t<n; t++) {
		cin >> s;
		int cur = 0, tans = 0;
		for(int i=0, j=s.size()-1; i<s.size(); i++, j--) {
			int ch = (s[i]-'A')*26 + (s[j]-'A');
			cur = trie_nxt(cur, ch);
			tans = max(tans, dp[cur]);
		}
		tans++;
		dp[cur] = max(dp[cur], tans);
		ans = max(ans, tans);
	}
	cout << ans;
}
