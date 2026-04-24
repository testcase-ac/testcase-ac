#include <bits/stdc++.h>
using namespace std;
const int MX = 10005;
vector<int> adj[2*MX];
struct SAT {
	vector<int> val, num, low, stk, scc, visiting;
	int nxt, n, cnt;
	int f(int i) {
		if(i < 0) i = -i+MX;
		return i;
	}
	int neg(int i) {
		if(i >= MX)
			return i-MX;
		else
			return i+MX;
	}
	SAT() {
		val.resize(2*MX);
		num.resize(2*MX);
		low.resize(2*MX);
		scc.resize(2*MX);
		visiting.resize(2*MX);
		nxt = 1;
		int k;
		cin >> k >> n;
		for(int i=0; i<k; i++) {
			int a, b;
			cin >> a >> b;
			a = f(a), b = f(b);
			//printf("%d->%d, %d->%d\n", neg(a), b, neg(b), a);
			adj[neg(a)].push_back(b);
			adj[neg(b)].push_back(a);
		}
	}
	void compute() {
		for(int i=1; i<=n; i++) {
			if(!num[i]) {
				//printf("dfs into %d\n", i);
				dfs(i);
			}
		}
		for(int i=MX+1; i<=MX+n; i++) {
			if(!num[i]) {
				//printf("dfs into %d\n", i);
				dfs(i);
			}
		}
	}
	void dfs(int i) {
		num[i] = low[i] = nxt++;
		visiting[i] = 1;
		stk.push_back(i);
		for(int a: adj[i]) {
			if(!num[a]) {
				dfs(a);
			}
			if(visiting[a]) {
				low[i] = min(low[i], low[a]);
			}
		}
		if(num[i] == low[i]) {
			int c = cnt++;
			while(1) {
				int t = stk.back();
				stk.pop_back();
				scc[t] = c;
				visiting[t] = 0;
				if(t == i) break;
			}
		}
	}
	bool out() {
		bool ok = 1;
		for(int i=1; i<=n; i++) {
			//printf("at i=%d, neg is %d. scc is %d, %d\n", i, neg(i), scc[i], scc[neg(i)]);
			if(scc[i] == scc[neg(i)]) {
				ok = 0;
			}
		}
		return ok;
		//cout << ok << '\n';
		// if(ok) {
		// 	for(int i=1; i<=n; i++) {
		// 		cout << (scc[i] < scc[neg(i)]) << ' ';
		// 	}
		// }
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	SAT sat;
	sat.compute();
	cout << (sat.out() ? "^_^" : "OTL");
}
