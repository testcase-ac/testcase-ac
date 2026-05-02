#include "testlib.h"

#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct Edge { int v, id; };

array<vector<Edge>, 100000> adj;
array<int, 100000> nid, low, par;
vector<int> st;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    for (int i = 0; i < m; i++) {
        int u = inf.readInt()-1;
        int v = inf.readInt()-1;

        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
    }

    st.reserve(n);

    int t = 0, leaf_cnt = 0, bridge_any = -1;
    auto tarjan = [&](auto&& self, int u, int p_id) -> int {
        low[u] = nid[u] = ++t;

        st.push_back(u);
        int adj_bcc = 0;

        for (auto& [v, id] : adj[u]) {
            if (id == p_id) { continue; }

            if (nid[v] == 0) {
                adj_bcc += self(self, v, id);
                par[v] = u;
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], nid[v]);
            }
        }

        if (low[u] == nid[u]) {
            adj_bcc += p_id != -1;

            while (true) {
                int v = st.back(); st.pop_back();
                if (v == u) { break; }
            }
            if (adj_bcc == 1) {
                leaf_cnt++;
                if (p_id != -1) { bridge_any = u; }
            }

            return 1;
        }
        return adj_bcc;
    };

    tarjan(tarjan, 0, -1);
    int r = ouf.readInt();

    if (leaf_cnt >= 2) {
        quitif(r > (leaf_cnt+1)/2, _wa, "suboptimal number of edges: expected %d, got %d", (leaf_cnt+1)/2, r);
        for (int i = 0; i < r; i++) {
            int u = ouf.readInt()-1;
            int v = ouf.readInt()-1;

            adj[u].push_back({ v, m+i });
            adj[v].push_back({ u, m+i });
        }

        t = 0; leaf_cnt = 0;
        for (int i = 0; i < n; i++) { nid[i] = 0; }
        tarjan(tarjan, 0, -1);

        quitif(leaf_cnt >= 2, _wa, "removing edge %d-%d disconnects the graph", bridge_any+1, par[bridge_any]+1);
    } else {
        quitif(r > 0, _wa, "suboptimal number of edges: expected 0, got %d", r);
    }
    
    quitf(_ok, "mazassumnida!!");
    return 0;
}
