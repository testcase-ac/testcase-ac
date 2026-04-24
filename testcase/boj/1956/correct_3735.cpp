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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> prev, curr(n, vector<int>(n, MOD));
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		curr[a][b] = c;
	}
	prev = curr;
	rep(i,n) prev[i][i] = 0;
	int ans = MOD;
	rep(k,n) {
		rep(i,n) rep(j,n) {
			if(i == j && i != k && prev[i][k] + prev[k][j] < MOD) 
				ans = min(prev[i][k] + prev[k][j], ans);
			curr[i][j] = min(prev[i][j], prev[i][k]+prev[k][j]);
		}
		prev = curr;
	}
	cout << (ans == MOD ? -1 : ans);
}
