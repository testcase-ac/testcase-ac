#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);

    int N;
    if (scenario == 4) { // disconnected
        N = rnd.next(7, 15);
    } else if (scenario == 3) { // dense
        N = rnd.next(5, 10);
    } else if (scenario == 1 || scenario == 2) { // star or random tree
        N = rnd.next(5, 12);
    } else { // path
        N = rnd.next(5, 10);
    }

    static bool used[101][101];
    memset(used, 0, sizeof(used));

    vector<pair<int,int>> edges;
    vector<int> deg(N + 1, 0);

    auto addEdge = [&](int u, int v) -> bool {
        if (u == v) return false;
        if (u > v) swap(u, v);
        if (used[u][v]) return false;
        used[u][v] = used[v][u] = true;
        edges.emplace_back(u, v);
        deg[u]++; deg[v]++;
        return true;
    };

    if (scenario == 0) {
        // Path
        for (int i = 1; i < N; i++) addEdge(i, i + 1);
        // Maybe one extra cross edge
        if (rnd.next(0, 1) == 1) {
            int attempts = 0;
            while (attempts < 30) {
                int u = rnd.next(1, N);
                int v = rnd.next(1, N);
                if (abs(u - v) <= 1) { attempts++; continue; }
                if (addEdge(u, v)) break;
                attempts++;
            }
        }
    } else if (scenario == 1) {
        // Star
        int c = rnd.next(1, N);
        for (int v = 1; v <= N; v++)
            if (v != c) addEdge(c, v);
        int maxExtra = (N - 1) * (N - 2) / 2;
        maxExtra = min(maxExtra, 3);
        int extraEdges = rnd.next(0, maxExtra);
        for (int k = 0; k < extraEdges; k++) {
            int attempts = 0;
            while (attempts < 30) {
                int a = rnd.next(1, N);
                int b = rnd.next(1, N);
                if (a == b || a == c || b == c) { attempts++; continue; }
                if (addEdge(a, b)) break;
                attempts++;
            }
        }
    } else if (scenario == 2) {
        // Random tree + few extra edges
        for (int v = 2; v <= N; v++) {
            int p = rnd.next(1, v - 1);
            addEdge(p, v);
        }
        int maxExtra = min(3, N * (N - 1) / 2 - (N - 1));
        int extraEdges = rnd.next(0, maxExtra);
        for (int k = 0; k < extraEdges; k++) {
            int attempts = 0;
            while (attempts < 40) {
                int u = rnd.next(1, N);
                int v = rnd.next(1, N);
                if (u == v) { attempts++; continue; }
                if (addEdge(u, v)) break;
                attempts++;
            }
        }
    } else if (scenario == 3) {
        // Dense graph
        int full = N * (N - 1) / 2;
        int cap = min(full, 40);
        int low = max(1, cap * 2 / 3);
        int Mtarget = rnd.next(low, cap);

        vector<pair<int,int>> all;
        all.reserve(full);
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());

        for (int i = 0; i < Mtarget; i++) {
            int u = all[i].first;
            int v = all[i].second;
            addEdge(u, v);
        }
    } else if (scenario == 4) {
        // Disconnected graph: several components, each at least 1 vertex
        int compCnt = rnd.next(2, 3);
        vector<int> sizes(compCnt, 1);
        int remaining = N - compCnt;
        for (int i = 0; i < remaining; i++) {
            int idx = rnd.next(0, compCnt - 1);
            sizes[idx]++;
        }

        vector<vector<int>> comps;
        comps.reserve(compCnt);
        int cur = 1;
        for (int i = 0; i < compCnt; i++) {
            vector<int> comp;
            for (int j = 0; j < sizes[i]; j++)
                comp.push_back(cur++);
            comps.push_back(comp);
        }

        // Build a tree in each nontrivial component
        for (auto &comp : comps) {
            int sz = (int)comp.size();
            if (sz <= 1) continue;
            for (int idx = 1; idx < sz; idx++) {
                int parentIdx = rnd.next(0, idx - 1);
                int u = comp[parentIdx];
                int v = comp[idx];
                addEdge(u, v);
            }
        }

        // Add a few extra edges within components
        vector<pair<int,int>> cand;
        for (auto &comp : comps) {
            int sz = (int)comp.size();
            for (int i = 0; i < sz; i++) {
                for (int j = i + 1; j < sz; j++) {
                    int u = comp[i], v = comp[j];
                    if (u > v) swap(u, v);
                    if (!used[u][v]) cand.emplace_back(u, v);
                }
            }
        }
        shuffle(cand.begin(), cand.end());
        int maxExtraGlobal = min({(int)cand.size(), 40 - (int)edges.size(), 5});
        if (maxExtraGlobal < 0) maxExtraGlobal = 0;
        int extraEdges = (maxExtraGlobal > 0) ? rnd.next(0, maxExtraGlobal) : 0;
        for (int i = 0; i < extraEdges; i++) {
            addEdge(cand[i].first, cand[i].second);
        }
    }

    // Choose starting vertex R with some variety
    int R;
    int choice = rnd.next(0, 4);
    if (choice == 0) {
        R = rnd.next(1, N);
    } else if (choice == 1) {
        R = 1;
    } else if (choice == 2) {
        R = N;
    } else if (choice == 3) {
        int maxd = 0;
        for (int i = 1; i <= N; i++) maxd = max(maxd, deg[i]);
        vector<int> cand;
        for (int i = 1; i <= N; i++)
            if (deg[i] == maxd) cand.push_back(i);
        R = rnd.any(cand);
    } else {
        vector<int> iso;
        for (int i = 1; i <= N; i++)
            if (deg[i] == 0) iso.push_back(i);
        if (!iso.empty()) R = rnd.any(iso);
        else R = rnd.next(1, N);
    }

    sort(edges.begin(), edges.end());

    println(N, (int)edges.size(), R);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
