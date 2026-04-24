#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

struct comp {
	bool operator()(int a, int b) {
		return a > b;
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> next(n);
	vector<int> last(n);
	rep(i, m) {
		int u,v;
		cin >> u >> v;
		u--, v--;
		next[u].push_back(v);
		last[v]++;
	}
	priority_queue<int, vector<int>, comp> pq;
	rep(i, n) {
		if(!last[i])
			pq.push(i);
	}
	vector<int> ans;
	while(!pq.empty()) {
		int t = pq.top();
		pq.pop();
		for(int nx: next[t]) {
			last[nx]--;
			if(!last[nx])
				pq.push(nx);
		}
		ans.push_back(t);
	}
	for(int a: ans)
		cout << (a+1) << ' ';
}
