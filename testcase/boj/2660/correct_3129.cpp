#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<vector<int>> prev(n, vector<int>(n, MOD)), curr(n, vector<int>(n));
	rep(i,n) prev[i][i] = 0;
	int a, b;
	while(1) {
		cin >> a >> b;
		if(a == -1) break;
		a--, b--;
		prev[a][b] = prev[b][a] = 1;
	}
	rep(k,n) {
		rep(i,n) rep(j,n) {
			curr[i][j] = min(prev[i][j], prev[i][k]+prev[k][j]);
		}
		prev = curr;
	}
	vector<int> ans;
	int val = MOD;
	rep(i,n) {
		int tval = *max_element(curr[i].begin(), curr[i].end());
		if(tval < val) {
			ans = {i+1};
			val = tval;
		}
		else if(tval == val) ans.push_back(i+1);
	}
	cout << val << ' ' << sz(ans) << '\n';
	for(int v: ans) cout << v << ' ';
}
