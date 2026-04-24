#include <bits/stdc++.h>
using namespace std;

vector<string> bucket[26];
int ind[26];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, n;
	cin >> k >> n;
	while(k--) {
		string s;
		cin >> s;
		bucket[s[0]-'a'].push_back(s);
	}
	for(int i=0; i<26; i++) {
		sort(bucket[i].begin(), bucket[i].end());
	}
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		int j = s[0]-'a';
		cout << bucket[j][ind[j]++] << '\n';
		if(ind[j] == bucket[j].size())
			ind[j] = 0;
	}
}
