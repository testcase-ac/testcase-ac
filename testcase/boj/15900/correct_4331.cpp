#include <bits/stdc++.h>
using namespace std;

vector<int> adj[500000];
bool seen[500000];
long long sum = 0;
void dfs(int i, int depth) {
	bool godown = false;
	seen[i] = true;
	for(int a: adj[i]) {
		if(!seen[a]) {
			godown = true;
			dfs(a, depth+1);
		}
	}
	if(!godown) sum += depth;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}
	dfs(0, 0);
	if(sum&1) cout << "Yes";
	else cout << "No";
}
