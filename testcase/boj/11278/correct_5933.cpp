#include <bits/stdc++.h>
using namespace std;
const int MX = 10005;
struct SAT {
	vector<vector<int>> adj;
	vector<int> val, num, low, stk, scc, visiting;
	int nxt, n, cnt;
	int f(int i) {
		if(i < 0) i = -i+MX;
		return i;
	}
	int neg(int i) {
		if(i >= MX)
			return i-MX;
		return i + MX;
	}
	SAT() {
		adj.resize(2*MX);
		val.resize(2*MX);
		num.resize(2*MX);
		low.resize(2*MX);
		scc.resize(2*MX);
		visiting.resize(2*MX);
		nxt = 1;
		int k;
		cin >> n >> k;
		for(int i=0; i<k; i++) {
			int a, b;
			cin >> a >> b;
			a = f(a), b = f(b);
			adj[neg(a)].push_back(b);
			adj[neg(b)].push_back(a);
		}
	}
	void compute() {
		for(int i=1; i<=n; i++) {
			if(!num[i])
				dfs(i);
		}
		for(int i=MX+1; i<=MX+n; i++) {
			if(!num[i])
				dfs(i);
		}
	}
	void dfs(int i) {
		num[i] = low[i] = nxt++;
		//printf("entered i=%d, allocated %d\n", i, num[i]);
		visiting[i] = 1;
		stk.push_back(i);
		for(int a: adj[i]) {
			if(!num[a]) {
				//printf("visit %d from %d\n", a, i);
				dfs(a);
			}
			if(visiting[a]) {
				low[i] = min(low[i], low[a]);
			}
		}
		//printf("finished i=%d. num=%d, low=%d\n", i, num[i], low[i]);
		if(num[i] == low[i]) {
			//printf("ended root=%d\n", i);
			int c = cnt++;
			while(1) {
				int t = stk.back();
				//printf("  it has %d\n", t);
				stk.pop_back();
				scc[t] = c;
				visiting[t] = 0;
				if(t == i) break;
			}
		}
	}
	void out() {
		bool ok = 1;
		for(int i=1; i<=n; i++) {
			if(scc[i] == scc[neg(i)])
				ok = 0;
		}
		cout << ok << '\n';
		if(ok) {
			for(int i=1; i<=n; i++) {
				cout << (scc[i] < scc[neg(i)]) << ' ';
			}
		}
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	SAT sat;
	sat.compute();
	sat.out();
}
