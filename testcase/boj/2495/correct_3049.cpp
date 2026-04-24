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
	for(int t=1; t<=3; t++) {
		string s;
		cin >> s;
		int cnt = 1, ans = 1;
		for(int i=1; i<8; i++) {
			if(s[i] == s[i-1]) {
				cnt++;
				ans = max(ans, cnt);
			} else {
				cnt = 1;
			}
		}
		cout << ans << '\n';
	}

}
