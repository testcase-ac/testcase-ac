#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans;
struct DSU {
    vector<int> par, g, p, counter;
    int n;
    DSU(int a, vector<int> _g, vector<int> _p) {
        n = a;
        par.resize(n);
        counter.resize(n, -1);
        g = _g;
        p = _p;
        for(int i=0; i<n; i++) {
            par[i] = i;
        }
    }
    int find(int i) {
        return i == par[i] ? i : par[i] = find(par[i]);
    }
    int merge(int i, int j) {
    	if(i == -1 || j == -1) return max(i, j);
    	i = find(i), j = find(j);
    	if(i == j)
    		return i;
    	par[j] = i;
    	g[i] += g[j];
    	p[i] += p[j];
    	return i;
    }
    void join(int i, int j) {
    	i = find(i), j = find(j);
    	if(i != j) {
    		st(i, -1);
    		st(j, -1);
    		int r1 = merge(i, j), r2 = merge(counter[i], counter[j]);
    		counter[r1] = r2;
    		if(r2 != -1)
    			counter[r2] = r1;
    		st(r1);
    	}
    }
    void diff(int i, int j) {
    	i = find(i), j = find(j);
    	if(i != counter[j]) {
    		st(i, -1);
    		st(j, -1);
    		int r1 = merge(i, counter[j]), r2 = merge(j, counter[i]);
    		counter[r1] = r2;
    		counter[r2] = r1;
    		st(r1);
    	}
    }
    void st(int t, int f=1) {
    	t = find(t);
    	if(counter[t] == -1) {
    		ans += min(g[t], p[t])*f;
    	} else {
    		counter[t] = find(counter[t]);
    		ans += min(g[t]+p[counter[t]], p[t]+g[counter[t]])*f;
    	}
    }
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, d;
	cin >> n >> d;
	vector<int> g(n), p(n);
	for(int i=0; i<n; i++) {
		cin >> g[i] >> p[i];
	}
	DSU dsu(n, g, p);
	for(int i=0; i<n; i++) {
		dsu.st(i);
	}
	for(int i=0; i<d; i++) {
		int c, a, b;
		cin >> c >> a >> b;
		a--, b--;
		if(c == 0) {
			dsu.join(a, b);
		} else {
			dsu.diff(a, b);
		}
	}
	cout << ans << '\n';
	int q;
	cin >> q;
	while(q--) {
		int c, a, b;
		cin >> c >> a >> b;
		if(c == 0) {
			dsu.join(a-1, b-1);
		} else if(c == 1) {
			dsu.diff(a-1, b-1);
		} else if(c == 2) {
			a--;
			dsu.st(a, -1);
			int dif = b - g[a];
			g[a] = b;
			dsu.g[dsu.find(a)] += dif;
			dsu.st(a);
		} else {
			a--;
			dsu.st(a, -1);
			int dif = b - p[a];
			p[a] = b;
			dsu.p[dsu.find(a)] += dif;
			dsu.st(a);
		}
		cout << ans << '\n';
	}
}
