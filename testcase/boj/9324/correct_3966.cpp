#include <bits/stdc++.h>
using namespace std;

bool solve() {
	string s;
	cin >> s;
	int n = s.size();
	int cnt[26] = {};
	for(int i=0; i<n; i++) {
		int t = s[i]-'A';
		cnt[t]++;
		if(cnt[t] % 3 == 0) {
			if(!(i+1 < n && s[i+1] == s[i]))
				return 0;
			i++;
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		cout << (solve() ? "OK\n" : "FAKE\n");
	}
}
