#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define def function
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	while(m--) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	queue<int> que;
	vector<bool> seen(n);
	que.push(0);
	seen[0] = true;
	int ans = 0;
	rep(i, 2) {
		int s = sz(que);
		while(s--) {
			int q = que.front();
			que.pop();
			for(int a: adj[q]) {
				if(!seen[a]) {
					seen[a] = true;
					que.push(a);
				}
			}
		}
		//printf("at i=%d, sz(que)=%d", i, sz(que));
		ans += sz(que);
	}
	cout << ans;
}
