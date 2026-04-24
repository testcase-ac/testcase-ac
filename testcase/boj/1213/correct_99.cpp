#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	cin >> s;
	int cnt[26] = {};
	for(char c: s) cnt[c-'A']++;
	int odd = -1;
	rep(i,26) {
		if(cnt[i] % 2) {
			if(sz(s) % 2 == 0 || odd != -1)
				return !(cout << "I'm Sorry Hansoo");
			odd = i;
		}
	}
	for(int i=0; i<26; i++) {
		rep(j, cnt[i]/2) cout << (char)(i+'A');
	}
	if(odd != -1) cout << (char)(odd+'A');
	for(int i=25; i>=0; i--) {
		rep(j, cnt[i]/2) cout << (char)(i+'A');
	}
}
