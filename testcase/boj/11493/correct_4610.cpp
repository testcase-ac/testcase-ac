#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int u, v, w, cap, flow;
};
const int INF = 0x3f3f3f3f;
struct MCMF {
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> par, dist, inque;
    MCMF(int _n) {
        n = _n;
        adj.resize(n+1);
        par.resize(n+1);
        dist.resize(n+1);
        inque.resize(n+1);
    }
    void addedge(int u, int v, int cap, int w) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, w, cap, 0});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, -w, cap, cap});
    }
    void spfa(int src) {
        fill(par.begin(), par.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(inque.begin(), inque.end(), 0);
        dist[src] = 0;
        queue<int> que({src});
        while(que.size()) {
            int q = que.front();
            que.pop();
            inque[q] = 0;
            for(int i: adj[q]) {
                Edge& e = edges[i];
                if(e.flow < e.cap && dist[e.v] > dist[e.u]+e.w) {
                    dist[e.v] = dist[e.u]+e.w;
                    par[e.v] = i;
                    if(!inque[e.v]) {
                        inque[e.v] = 1;
                        que.push(e.v);
                    }
                }
            }
        }
    }
    pair<int, int> solve(int src, int sink) {
        int mc = 0, mf = 0;
        while(1) {
            spfa(src);
            if(par[sink] == -1)
                return {mc, mf};
            int flow = INF, c = sink;
            while(c != src) {
                Edge &e = edges[par[c]];
                flow = min(flow, e.cap-e.flow);
                c = e.u;
            }
            c = sink;
            while(c != src) {
                Edge &e = edges[par[c]], &ie = edges[par[c]^1];
                e.flow += flow;
                ie.flow -= flow;
                c = e.u;
            }
            mf += flow;
            mc += dist[sink]*flow;
        }
    }
};
int dist[501][501], node[501], coin[501], tonode[501], tocoin[501];
int solve() {
	memset(dist, 0x3f, sizeof dist);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++)
		dist[i][i] = 0;
	for(int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		dist[u][v] = dist[v][u] = 1;
	}
	for(int k=1; k<=n; k++) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}
	int a = 0, b = 0;
	for(int i=1; i<=n; i++) {
		cin >> node[i];
		if(node[i])
			tonode[a++] = i;
	}
	for(int i=1; i<=n; i++) {
		cin >> coin[i];
		if(coin[i])
			tocoin[b++] = i;
	}
	MCMF mcmf(a+b+2);
	for(int i=0; i<a; i++) {
		mcmf.addedge(a+b, i, 1, 0);
	}
	for(int i=a; i<a+b; i++) {
		mcmf.addedge(i, a+b+1, 1, 0);
	}
	for(int i=0; i<a; i++) {
		for(int j=0; j<b; j++) {
			//printf("%d->%d is in fact %d->%d, and it has weight %d\n", i, j, tonode[i], tocoin[j], dist[tonode[i]][tocoin[j]]);
			mcmf.addedge(i, a+j, 1, dist[tonode[i]][tocoin[j]]);
		}
	}
	return mcmf.solve(a+b, a+b+1).first;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		cout << solve() << '\n';

}
