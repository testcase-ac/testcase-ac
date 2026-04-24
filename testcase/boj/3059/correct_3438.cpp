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
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		bool seen[26] = {};
		for(char c: s) {
			seen[c-'A'] = true;
		}
		int ans = 0;
		rep(i,26)
			if(!seen[i]) ans += (i+'A');
		cout << ans << '\n';
	}
}
