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
    void addedge(int u, int v, int w, int cap) {
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
    int ans = 0;
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
            ans = min(ans, mc);
        }
    }
};

int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int cost[][4] = {{100,70,40,0},{70,50,30,0},{40,30,20,0},{0,0,0,0}};
char arr[50][51];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R;
    C = R;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'F')
				arr[i][j] -= 2;
			arr[i][j] -= 'A';
		}
	}
	MCMF mcmf(R*C+2);
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if((i+j)%2) {
				mcmf.addedge(R*C, i*C+j, 0, 1);
				for(int k=0; k<4; k++) {
					int tr = i+dr[k], tc = j+dc[k];
					if(!(0 <= tr && tr < R && 0 <= tc && tc < C)) continue;
					mcmf.addedge(i*C+j, tr*C+tc, -cost[arr[i][j]][arr[tr][tc]], 1);
				}
			} else {
				mcmf.addedge(i*C+j, R*C+1, 0, 1);
			}
		}
	}
	mcmf.solve(R*C, R*C+1);
	cout << -mcmf.ans;
}
