#include <bits/stdc++.h>
using namespace std;
const int MX = 4e6+1;
int arr[MX][26], dp[MX], nxt = 1;
int32_t main() {
	string s, a, b;
	cin >> s >> a >> b;
	vector<int> ends(s.size());
	for(int i=0; i+b.size()<=s.size(); i++) {
		if(s.substr(i, b.size()) == b) {
			ends[i+b.size()-1] = 1;
		}
	}
	for(int st=0; st+a.size()<=s.size(); st++) {
		int cur = 0;
		for(int i=st; i<s.size(); i++) {
			int c = s[i]-'a';
			if(!arr[cur][c]) {
				arr[cur][c] = nxt++;
			}
			cur = arr[cur][c];
			if(ends[i] && i-b.size()+1 >= st)
				dp[cur] = 1;
		}
	}
	for(int i=nxt-1; i; i--) {
		for(int j=0; j<26; j++) {
			if(arr[i][j])
				dp[i] += dp[arr[i][j]];
		}
	}
	int cur = 0;
	for(char c: a) {
		cur = arr[cur][c-'a'];
	}
	cout << dp[cur];
}
