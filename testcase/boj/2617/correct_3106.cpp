#include <bits/stdc++.h>
using namespace std;
const int MX = 1000;
vector<int> adjf[MX], adjt[MX];
bool seen[MX], arr[MX];
int dfs(int i) {
	seen[i] = 1;
	int ret = 1;
	for(int a: adjf[i]) {
		if(!seen[a])
			ret += dfs(a);
	}
	return ret;
}
int dfs2(int i) {
	seen[i] = 1;
	int ret = 1;
	for(int a: adjt[i]) {
		if(!seen[a])
			ret += dfs2(a);
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		adjf[a].push_back(b);
		adjt[b].push_back(a);
	}
	int th = (n+1)/2;
	for(int i=1; i<=n; i++) {
		memset(seen, 0, sizeof seen);
		if(dfs(i) > th)
			arr[i] = 1;
	}
	for(int i=1; i<=n; i++) {
		memset(seen, 0, sizeof seen);
		if(dfs2(i) > th)
			arr[i] = 1;
	}
	cout << accumulate(arr, arr+n+1, 0);
}
