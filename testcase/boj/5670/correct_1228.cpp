#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n;
	if(!(cin >> n))
		exit(0);
	vector<string> arr(n);
	vector<vector<int>> trie(1, vector<int>(27));
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(string& s: arr) {
		int t = 0;
		for(char c: s) {
			c -= 'a';
			if(!trie[t][c]) {
				trie[t][c] = trie.size();
				trie.push_back(vector<int>(27));
			}
			t = trie[t][c];
		}
		trie[t][26] = 1;
	}
	int total = 0;
	for(string& s: arr) {
		int t = 0;
		for(char c: s) {
			c -= 'a';
			int cnt = 0;
			for(int i=0; i<27; i++) {
				if(trie[t][i])
					cnt++;
			}
			if(!(t && cnt == 1))
				total++;
			t = trie[t][c];
		}
	}
	cout << fixed << setprecision(2) << (double)total/n << '\n';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		solve();
	}
}
