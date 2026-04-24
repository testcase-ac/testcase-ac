#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <functional>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define set0v(v) memset(&v[0], 0, v.size() * sizeof v[0])
#define deb(v) cout << #v << ':' << v

using namespace std;


int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	while(m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
	}
	vector<int> cnt(n), seen(n);
	function<void(int)> dfs = [&](int i) {
		seen[i] = true;
		for(int a: adj[i]) {
			if(!seen[a])
				dfs(a);
		}
		cnt[i]++;
	};
	rep(i, n) {
		dfs(i);
		fill(seen.begin(), seen.end(), 0);
	}
	vector<int> ans;
	int mx = 0;
	rep(i, n) {
		if(cnt[i] > mx) {
			ans = {i+1};
			mx = cnt[i];
		}
		else if(cnt[i] == mx)
			ans.push_back(i+1);
	}
	for(int a: ans)
		cout << a << ' ';
}
