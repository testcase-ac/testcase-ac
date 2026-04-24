#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 100003;
vector<vector<int>> adj(MX), adjt(MX);
stack<int> st;
bool seen[MX];
vector<vector<int>> cc;
void dfs1(int i) {
    seen[i] = true;
    for(int a: adj[i]) {
        if(!seen[a])
            dfs1(a);
    }
    st.push(i);
}
void dfs2(int i) {
    seen[i] = true;
    cc.back().push_back(i);
    for(int a: adjt[i]) {
        if(!seen[a])
            dfs2(a);
    }
}
void scc(int v) {
	memset(seen, 0, sizeof seen);
    for(int i=0; i<v; i++)
        if(!seen[i])
            dfs1(i);
    memset(seen, 0, sizeof seen);
    while(!st.empty()) {
        int i = st.top();
        st.pop();
        if(!seen[i]) {
            cc.emplace_back();
            dfs2(i);
        }
    }
}

int seencnt = 0;
void visit(int t) {
	if(seen[t])
		return;
	seen[t] = 1;
	seencnt++;
	for(int i: adj[t])
		visit(i);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		for(int i=0; i<n; i++) {
			adj[i].clear();
			adjt[i].clear();
		}
		cc.clear();
		for(int i=0; i<m; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adjt[v].push_back(u);
		}
		scc(n);
		seencnt = 0;
		memset(seen, 0, sizeof seen);
		visit(cc.front().front());
		if(seencnt == n) {
			sort(cc.front().begin(), cc.front().end());
			for(int x: cc.front()) {
				cout << x << '\n';
			}
			cout << '\n';
		} else {
			cout << "Confused\n\n";
		}
	}
}
