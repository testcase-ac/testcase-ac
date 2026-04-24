#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+1;
pair<int, int> arr[MX];
int ans[MX];
vector<pair<int, int>> adj[MX]; // edge no, to where
bool used[MX], seen[MX];
void go(int s, int t) {
	//printf("letting edge %d to use node %d\n", s, t);
	ans[s] = t;
	if(used[t]) {
		cout << "-1\n";
		exit(0);
	}
	used[t] = 1;
}
void dfs(int u, int e, int par) {
	if(seen[u]) return;
	//printf("enter u=%d\n", u);
	//if(par != -1) printf("dfs used edge %d->%d. edge number is %d\n", par, u, e);
	seen[u] = 1;
	for(auto pr: adj[u]) {
		int i, v;
		tie(i, v) = pr;
		dfs(v, i, u);
	}
	if(e != -1) {
		if(!used[u])
			go(e, u);
		else
			go(e, par);
	}
	for(auto pr: adj[u]) {
		if(pr.second == par || ans[pr.first] != 0x3f3f3f3f) continue;
		if(!used[u])
			go(pr.first,u);
		else
			go(pr.first,pr.second);
	}
	//printf("exit u=%d\n", u);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(ans, 0x3f, sizeof ans);
	int n;
	cin >> n;
	map<pair<int,int>,int> mp;
	for(int i=0; i<n; i++) {
		cin >> arr[i].first >> arr[i].second;
		if(arr[i].first > arr[i].second)
			swap(arr[i].first, arr[i].second);
		else if(arr[i].first == arr[i].second) {
			go(i, arr[i].first);
			continue;
		}
		if(mp.count(arr[i])) {
			go(mp[arr[i]], arr[i].first);
			go(i, arr[i].second);
			mp[arr[i]] = -1;
		} else {
			mp[arr[i]] = i;
		}
	}
	for(int i=1; i<MX; i++)
		seen[i] = 1;
	for(auto pr: mp) {
		if(pr.second != -1) {
			int u, v, i;
			tie(u, v) = pr.first;
			i = pr.second;
			adj[u].push_back({i, v});
			adj[v].push_back({i, u});
			seen[u] = seen[v] = 0;
		}
	}
	for(int i=1; i<MX; i++) {
		dfs(i, -1, -1);
	}
	for(int i=0; i<n; i++)
		cout << ans[i] << '\n';
}
