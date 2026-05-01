#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(5, 12);
    int M, R;
    vector<pair<int,int>> edges;
    vector<vector<bool>> adj(N+1, vector<bool>(N+1, false));
    int type = rnd.next(0, 4);

    if (type == 0) {
        // Random graph with random density
        vector<pair<int,int>> all;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        int maxM = (int)all.size();
        double dens = rnd.next();
        int mlim = max(1, int(dens * maxM));
        M = rnd.next(1, mlim);
        edges.assign(all.begin(), all.begin() + M);
        R = rnd.next(1, N);
    }
    else if (type == 1) {
        // Random tree plus a few extra edges
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            int u = min(i, p), v = max(i, p);
            edges.emplace_back(u, v);
            adj[u][v] = adj[v][u] = true;
        }
        int extra = rnd.next(0, N / 4);
        vector<pair<int,int>> all;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                if (!adj[i][j])
                    all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        for (int k = 0; k < extra && k < (int)all.size(); k++)
            edges.push_back(all[k]);
        M = edges.size();
        R = rnd.next(1, N);
    }
    else if (type == 2) {
        // Star graph centered at R, plus extras
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) if (i != center) {
            int u = min(i, center), v = max(i, center);
            edges.emplace_back(u, v);
            adj[u][v] = adj[v][u] = true;
        }
        int extra = rnd.next(0, N / 4);
        vector<pair<int,int>> all;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                if (!adj[i][j])
                    all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        for (int k = 0; k < extra && k < (int)all.size(); k++)
            edges.push_back(all[k]);
        M = edges.size();
        R = center;
    }
    else if (type == 3) {
        // Disconnected: two components
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        int s = rnd.next(1, N - 1);
        vector<int> g1(perm.begin(), perm.begin() + s), g2(perm.begin() + s, perm.end());
        auto mk = [&](vector<int>& g) {
            if (g.size() < 2) return;
            for (int i = 1; i < (int)g.size(); i++) {
                int p = rnd.next(0, i - 1);
                int u = min(g[i], g[p]), v = max(g[i], g[p]);
                edges.emplace_back(u, v);
                adj[u][v] = adj[v][u] = true;
            }
        };
        mk(g1); mk(g2);
        int extra1 = rnd.next(0, (int)g1.size() / 2);
        int extra2 = rnd.next(0, (int)g2.size() / 2);
        auto addExtras = [&](vector<int>& g, int extra) {
            vector<pair<int,int>> all2;
            for (int i = 0; i < (int)g.size(); i++)
                for (int j = i + 1; j < (int)g.size(); j++) {
                    int u = min(g[i], g[j]), v = max(g[i], g[j]);
                    if (!adj[u][v]) all2.emplace_back(u, v);
                }
            shuffle(all2.begin(), all2.end());
            for (int k = 0; k < extra && k < (int)all2.size(); k++) {
                auto e = all2[k];
                edges.push_back(e);
                adj[e.first][e.second] = adj[e.second][e.first] = true;
            }
        };
        addExtras(g1, extra1);
        addExtras(g2, extra2);
        M = edges.size();
        R = rnd.any(g1);
    }
    else {
        // Complete graph
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                edges.emplace_back(i, j);
        M = edges.size();
        R = rnd.next(1, N);
    }

    shuffle(edges.begin(), edges.end());
    println(N, M, R);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
