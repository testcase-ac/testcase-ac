#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	rep(i, m) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int minans = INT_MAX, minindex;
	for(int i=n-1;i>=0;i--) {
		int ans = 0;
		queue<pair<int,int>> que; // index, level
		vector<bool> found(n);
		found[i] = true;
		for(int next: adj[i]) que.emplace(next, 1);
		while(!que.empty()) {
			auto pr = que.front();
			que.pop();
			if(found[pr.first]) continue;
			found[pr.first] = true;
			ans += pr.second;
			for(int next: adj[pr.first]) {
				if(!found[next]) {
					que.emplace(next, pr.second+1);
				}
			}
		}
		if(ans <= minans) {
			minans = ans;
			minindex = i;
		}
	}
	cout << minindex+1;
}
