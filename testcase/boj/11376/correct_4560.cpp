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

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define setn1(arr) memset(arr, -1, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n+m+2);
	int cap[n+m+2][n+m+2];
	set0(cap);
	for(int i=1; i<=n; i++) {
		int k;
		cin >> k;
		while(k--) {
			int v;
			cin >> v;
			cap[i][n+v] = 1;
			adj[i].push_back(n+v);
			adj[n+v].push_back(i);
		}
		cap[0][i] = 2;
		adj[0].push_back(i);
	}
	for(int i=n+1; i<=n+m; i++) {
		cap[i][n+m+1] = 1;
		adj[i].push_back(n+m+1);
	}
	int ans = 0;
	while(1) {
		queue<int> que;
		bool visited[n+m+2];
		int from[n+m+2];
		set0(visited);
		set0(from);
		que.push(0);
		visited[0] = true;
		while(!que.empty()) {
			int q = que.front();
			que.pop();
			for(int i: adj[q]) {
				if(cap[q][i] && !visited[i]) {
					visited[i] = true;
					from[i] = q;
					que.push(i);
					if(i == n+m+1) goto out;
				}
			}
		}
		out:;
		if(que.empty()) break;
		int where = n+m+1, mincap = MOD;
		while(where != 0) {
			int prev = from[where];
			mincap = min(mincap, cap[prev][where]);
			where = prev;
		}
		where = n+m+1;
		while(where != 0) {
			int prev = from[where];
			cap[prev][where] -= mincap;
			cap[where][prev] += mincap;
			where = prev;
		}
		ans += mincap;
	}
	cout << ans;
}
