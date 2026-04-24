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
	int n;
	cin >> n;
	string r;
	cin >> r;
	int cnt[26] = {}, ans = 0;
	for(char c: r) cnt[c-'A']++;
	rep(i,n-1) {
		string a;
		cin >> a;
		int tcnt[26] = {};
		for(char c: a) tcnt[c-'A']++;
		int p1 = 0, n1 = 0, ok=true;
		rep(j,26) {
			if(tcnt[j]-cnt[j] == 1) p1++;
			else if(tcnt[j]-cnt[j] == -1) n1++;
			else if(tcnt[j]-cnt[j]) ok = false;
		}
		if(ok && p1 <= 1 && n1 <= 1) ans++;
	}
	cout << ans;
}
