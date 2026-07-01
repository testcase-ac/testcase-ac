#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

long long randomT() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return 2;
    if (mode == 2) return rnd.next(3, 20);
    if (mode == 3) return rnd.next(21, 1000);
    if (mode == 4) return rnd.next(1001, 1000000);
    return rnd.next(999999999000LL, 1000000000000LL);
}

void addEdge(set<Edge>& seen, vector<Edge>& edges, int a, int b) {
    if (a > b) swap(a, b);
    if (seen.insert({a, b}).second) {
        edges.push_back({a, b});
    }
}

vector<Edge> shuffledAllEdges(int n) {
    vector<Edge> all;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            all.push_back({a, b});
        }
    }
    shuffle(all.begin(), all.end());
    return all;
}

vector<Edge> makeEdges(int n, int mode) {
    set<Edge> seen;
    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) addEdge(seen, edges, i, i + 1);
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) addEdge(seen, edges, center, v);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) addEdge(seen, edges, i, i % n + 1);
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int a = 1; a <= split; ++a) {
            for (int b = split + 1; b <= n; ++b) {
                if (rnd.next(0, 99) < 55) addEdge(seen, edges, a, b);
            }
        }
    } else if (mode == 4) {
        vector<Edge> all = shuffledAllEdges(n);
        int m = rnd.next(max(1, n - 1), static_cast<int>(all.size()));
        edges.assign(all.begin(), all.begin() + m);
        for (auto& edge : edges) seen.insert(edge);
    } else {
        int groups = rnd.next(2, min(4, n));
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                bool sameBand = (i % groups) == (j % groups);
                int chance = sameBand ? 45 : 12;
                if (rnd.next(0, 99) < chance) addEdge(seen, edges, i, j);
            }
        }
    }

    if (edges.empty()) {
        vector<Edge> all = shuffledAllEdges(n);
        const auto& edge = all.front();
        addEdge(seen, edges, edge.first, edge.second);
    }

    vector<Edge> all = shuffledAllEdges(n);
    int maxEdges = n * (n - 1) / 2;
    int target = rnd.next(static_cast<int>(edges.size()), maxEdges);
    for (const auto& edge : all) {
        if (static_cast<int>(edges.size()) >= target) break;
        addEdge(seen, edges, edge.first, edge.second);
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 5);
    println(k);
    for (int tc = 0; tc < k; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 4) {
            n = rnd.next(7, 10);
        } else {
            n = rnd.next(2, 10);
        }

        vector<Edge> edges = makeEdges(n, mode);
        println(n, static_cast<int>(edges.size()), randomT());
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
