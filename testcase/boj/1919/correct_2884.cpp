#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int cnts[2][26];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string a, b;
	cin >> a >> b;
	for(char c: a) cnts[0][c-'a']++;
	for(char c: b) cnts[1][c-'a']++;
	int ans = 0;
	rep(i,26) {
		ans += abs(cnts[0][i]-cnts[1][i]);
	}
	cout << ans;
}
