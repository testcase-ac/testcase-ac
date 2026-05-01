#include "testlib.h"
using namespace std;

struct Edge {
    int u, v;
    int w; // in tenths of miles
};

struct DSU {
    vector<int> p, r;
    DSU(int n) {
        p.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

int computeMST(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });
    DSU dsu(n);
    int total = 0;
    int used = 0;
    for (const auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            ++used;
            if (used == n - 1) break;
        }
    }
    return total;
}

vector<string> generateNames(int N, bool simple) {
    vector<string> names;
    if (simple) {
        names.resize(N);
        for (int i = 0; i < N; ++i) {
            char c = 'A' + i;
            names[i] = string(1, c);
        }
    } else {
        names.reserve(N);
        string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        while ((int)names.size() < N) {
            int len = rnd.next(3, 8);
            string s;
            s.reserve(len);
            for (int j = 0; j < len; ++j)
                s += rnd.any(alphabet);
            bool exists = false;
            for (const string &t : names) {
                if (t == s) {
                    exists = true;
                    break;
                }
            }
            if (!exists) names.push_back(s);
        }
    }
    return names;
}

vector<Edge> generateConnectedGraph(int N, int M) {
    vector<Edge> edges;
    edges.reserve(M);
    vector< vector<bool> > used(N, vector<bool>(N, false));

    vector<int> perm(N);
    for (int i = 0; i < N; ++i) perm[i] = i;
    shuffle(perm.begin(), perm.end());

    // Build a random spanning tree first (as a path)
    for (int i = 1; i < N; ++i) {
        int u = perm[i - 1];
        int v = perm[i];
        int w = rnd.next(1, 200); // 0.1 to 20.0
        edges.push_back({u, v, w});
        used[u][v] = used[v][u] = true;
    }

    int treeEdges = N - 1;
    int extra = M - treeEdges;
    if (extra > 0) {
        vector<pair<int,int>> cand;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (!used[i][j])
                    cand.push_back(make_pair(i, j));
        shuffle(cand.begin(), cand.end());
        for (int k = 0; k < extra; ++k) {
            int u = cand[k].first;
            int v = cand[k].second;
            int w = rnd.next(1, 200);
            edges.push_back({u, v, w});
            used[u][v] = used[v][u] = true;
        }
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4); // 0..4 for variety

    int N;
    vector<string> names;
    vector<Edge> edges;
    int M = 0;
    double spool = 0.0;

    if (scenario == 4) {
        // Single-house edge case
        N = 1;
        bool simpleNames = rnd.next(0, 1);
        names = generateNames(N, simpleNames);
        edges.clear();
        M = 0;
        int spoolTenths = rnd.next(0, 200); // 0.0 to 20.0
        spool = spoolTenths / 10.0;
    } else {
        // At least 2 houses, always generate a connected graph
        N = rnd.next(2, 7);
        bool simpleNames = rnd.next(0, 1);
        names = generateNames(N, simpleNames);

        int maxPairs = N * (N - 1) / 2;
        int maxM = min(maxPairs, 9);
        int desiredM;

        if (scenario == 0) {
            // Sometimes just a tree, sometimes with a few extra edges
            if (rnd.next(0, 1) == 0) desiredM = N - 1;
            else desiredM = rnd.next(N - 1, maxM);
        } else if (scenario == 1) {
            // Prefer denser graphs
            int lo = max(N - 1, maxM - 2);
            desiredM = rnd.next(lo, maxM);
        } else if (scenario == 2) {
            // Any connected size
            desiredM = rnd.next(N - 1, maxM);
        } else { // scenario == 3
            // Prefer trees (minimal edges)
            desiredM = N - 1;
        }

        edges = generateConnectedGraph(N, desiredM);
        M = (int)edges.size();

        int mstW = computeMST(N, edges); // in tenths
        int spoolTenths;

        if (scenario == 0) {
            int type = rnd.next(0, 2);
            if (type == 0) {
                // Exactly MST
                spoolTenths = mstW;
            } else if (type == 1) {
                // Slightly more than MST
                spoolTenths = mstW + rnd.next(1, 5);
            } else {
                // Slightly less than MST (but not negative)
                int dec = mstW < 5 ? mstW : 5;
                spoolTenths = mstW - rnd.next(1, dec);
            }
        } else if (scenario == 1) {
            // Not enough cable
            if (mstW > 1) spoolTenths = rnd.next(0, mstW - 1);
            else spoolTenths = 0;
        } else if (scenario == 2) {
            // Clearly enough cable
            spoolTenths = mstW + rnd.next(5, 50);
        } else { // scenario == 3
            // Mixed: sometimes enough, sometimes not, around MST
            int type = rnd.next(0, 3);
            if (type == 0) {
                spoolTenths = mstW;
            } else if (type == 1) {
                int dec = mstW < 20 ? mstW : 20;
                spoolTenths = mstW - (dec > 0 ? rnd.next(0, dec) : 0);
            } else if (type == 2) {
                spoolTenths = mstW + rnd.next(0, 20);
            } else {
                spoolTenths = rnd.next(0, mstW + 50);
            }
            if (spoolTenths < 0) spoolTenths = 0;
        }

        spool = spoolTenths / 10.0;
    }

    // Randomize edge directions and order
    for (auto &e : edges) {
        if (rnd.next(0, 1)) swap(e.u, e.v);
    }
    shuffle(edges.begin(), edges.end());

    // Output
    printf("%.1f\n", spool);
    println(N);
    for (int i = 0; i < N; ++i)
        println(names[i]);
    println(M);
    for (const auto &e : edges) {
        double dist = e.w / 10.0;
        printf("%s %s %.1f\n",
               names[e.u].c_str(),
               names[e.v].c_str(),
               dist);
    }

    return 0;
}
