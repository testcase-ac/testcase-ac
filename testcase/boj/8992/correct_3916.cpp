#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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

struct Line {
	int x, y, xp, yp, w;
};
bool in(int a, int mid, int b) {
	return (a <= mid && mid <= b) || (b <= mid && mid <= a);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n >> m;
		vector<Line> hor(n), ver(m);
		MCMF mcmf(n+m+2);
		for(int i=0; i<n; i++) {
			mcmf.addedge(n+m, i, 1, 0);
			cin >> hor[i].x >> hor[i].y >> hor[i].xp >> hor[i].yp >> hor[i].w;
		}
		for(int i=0; i<m; i++) {
			mcmf.addedge(i+n, n+m+1, 1, 0);
			cin >> ver[i].x >> ver[i].y >> ver[i].xp >> ver[i].yp >> ver[i].w;
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				if(in(ver[j].y, hor[i].y, ver[j].yp) && in(hor[i].x, ver[j].x, hor[i].xp))
					mcmf.addedge(i, n+j, 1, -hor[i].w*ver[j].w);
			}
		}
		auto pr = mcmf.solve(n+m, n+m+1);
		cout << pr.second << ' ' << -pr.first << '\n';
	}
}
