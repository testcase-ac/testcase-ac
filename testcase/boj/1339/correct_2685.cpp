#include <bits/stdc++.h>
using namespace std;

bool used[26];
int mp[26], mp2[10];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string words[n];
	vector<char> alpha;
	for(int i=0; i<n; i++) {
		cin >> words[i];
		for(char c: words[i]) {
			if(!used[c-'A']) {
				used[c-'A'] = true;
				alpha.push_back(c);
			}
		}
	}
	int m = alpha.size(), nxt = 9;
	for(int i=0; i<m; i++) {
		mp2[i] = nxt--;
	}
	int ans = 0;
	do {
		for(int i=0; i<m; i++)
			mp[alpha[i]-'A'] = mp2[i];
		int temp = 0;
		for(int i=0; i<n; i++) {
			int num = 0;
			for(char c: words[i]) {
				num *= 10;
				num += mp[c-'A'];
			}
			temp += num;
		}
		ans = max(ans, temp);
	} while(prev_permutation(mp2, mp2+m));
	cout << ans;
}
