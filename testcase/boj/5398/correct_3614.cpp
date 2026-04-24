#include <bits/stdc++.h>
using namespace std;
#define int long long
struct biparite {
    int n, m, s;
    vector<int> match, seen;
    vector<vector<int>> adj;
    biparite(int _n, int _m) {
        n = _n, m = _m;
        match.resize(m, -1);
        seen.resize(n, -1);
        adj.resize(n);
    }
    void addedge(int u, int v) {
        adj[u].push_back(v);
    }
    bool dfs(int i) {
        if(seen[i] == s)
            return 0;
        seen[i] = s;
        for(int a: adj[i]) {
            if(match[a] == -1 || dfs(match[a])) {
                match[a] = i;
                return 1;
            }
        }
        return 0;
    }
    int solve() {
        int ans = 0;
        for(int i=0; i<n; i++) {
            s = i;
            if(dfs(i))
                ans++;
        }
        return ans;
    }
};
char arr[2001][2001];
int num[2001][2001];
void solve() {
	int n, m;
	cin >> n >> m;
	biparite bip(n, m);
	memset(arr, 0, sizeof arr);
	for(int i=0; i<n; i++) {
		int x, y;
		string s;
		cin >> x >> y >> s;
		for(char c: s) {
			arr[y][x] = c;
			num[y][x] = i;
			x++;
		}
	}
	for(int i=0; i<m; i++) {
		int x, y;
		string s;
		cin >> x >> y >> s;
		for(char c: s) {
			if(arr[y][x] && arr[y][x] != c)
				bip.addedge(num[y][x], i);
			y++;
		}
	}
	cout << n+m-bip.solve() << '\n';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		solve();
}
