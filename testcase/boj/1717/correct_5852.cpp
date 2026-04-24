#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> par;
    vector<int> setsz;
    int n;
    DSU(int a) {
        n = a;
        par.resize(n);
        setsz.resize(n);
        for(int i=0; i<n; i++) {
            par[i] = i;
            setsz[i] = 1;
        }
    }
    int find(int i) {
        return i == par[i] ? i : par[i] = find(par[i]);
    }
    void join(int i, int j) {
        i = find(i), j = find(j);
        if(i != j) {
        	if(setsz[i] < setsz[j])
        		swap(i, j);
            par[j] = i;
            setsz[i] += setsz[j];
        }
    }
    bool sameset(int i, int j) {
        return find(i) == find(j);
    }
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	DSU dsu(n+1);
	while(m--) {
		int t, a, b;
		cin >> t >> a >> b;
		if(!t)
			dsu.join(a, b);
		else
			cout << (dsu.sameset(a, b) ? "YES\n" : "NO\n");
	}
}
