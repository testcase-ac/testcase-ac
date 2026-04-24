#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
int n;
inline bool isvalid(int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < n;
}
int di[] = {1,-1,0,0}, dj[] = {0,0,1,-1};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	string arr[n];
	bool seen[n][n] = {};
	rep(i,n) cin >> arr[i];
	queue<pair<int, int>> quewhite, queblack;
	seen[0][0] = true;
	quewhite.emplace(0,0);
	int ans = 0;
	while(1) {
		while(!quewhite.empty()) {
			auto pr = quewhite.front();
			quewhite.pop();
			rep(i,4) {
				int ti = pr.first + di[i], tj = pr.second + dj[i];
				if(!isvalid(ti,tj) || seen[ti][tj]) continue;
				if(ti == n-1 && tj == n-1) return !(cout << ans);
				seen[ti][tj] = true;
				if(arr[ti][tj] == '1') quewhite.emplace(ti,tj);
				else queblack.emplace(ti, tj);
			}
		}
		quewhite = queblack;
		queblack = queue<pair<int, int>>();
		ans++;
	}
}
