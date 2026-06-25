#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    long long l;
    long long r;
};

pair<long long, long long> randomInterval(long long center, int mode) {
    if (mode == 0) {
        long long x = rnd.next(1LL, 12LL);
        return {x, x};
    }
    if (mode == 1) {
        long long l = rnd.next(1LL, 10LL);
        long long r = rnd.next(l, min(20LL, l + rnd.next(0LL, 8LL)));
        return {l, r};
    }
    if (mode == 2) {
        long long l = max(1LL, center - rnd.next(0LL, 4LL));
        long long r = min(1000000000LL, center + rnd.next(0LL, 4LL));
        return {l, r};
    }

    long long l = rnd.next(999999990LL, 1000000000LL);
    long long r = rnd.next(l, 1000000000LL);
    return {l, r};
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, long long l, long long r) {
    if (u > v) {
        swap(u, v);
    }
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, l, r});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    if (mode >= 4) {
        n = rnd.next(2, 6);
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    long long focus = rnd.next(1LL, 20LL);

    if (mode == 0) {
        int pathLen = n - 1;
        for (int i = 1; i <= pathLen; ++i) {
            auto [l, r] = randomInterval(focus, rnd.next(1, 2));
            addEdge(edges, used, i, i + 1, l, r);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            auto [l, r] = randomInterval(focus, rnd.next(0, 2));
            addEdge(edges, used, rnd.next(1, v - 1), v, l, r);
        }
    } else if (mode == 2) {
        int split = rnd.next(2, n);
        for (int i = 1; i < split; ++i) {
            auto [l, r] = randomInterval(focus, 1);
            addEdge(edges, used, i, i + 1, l, r);
        }
        for (int i = split; i < n; ++i) {
            auto [l, r] = randomInterval(focus, 2);
            addEdge(edges, used, i, i + 1, l, r);
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            auto [l, r] = randomInterval(focus, rnd.next(0, 3));
            addEdge(edges, used, 1, v, l, r);
        }
    } else {
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int denseCount = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < denseCount; ++i) {
            auto [u, v] = candidates[i];
            auto [l, r] = randomInterval(focus, rnd.next(0, 3));
            addEdge(edges, used, u, v, l, r);
        }
    }

    int maxEdges = n * (n - 1) / 2;
    int target = rnd.next((int)edges.size(), min(maxEdges, 24));
    while ((int)edges.size() < target) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) {
            continue;
        }
        auto [l, r] = randomInterval(focus, rnd.next(0, 3));
        addEdge(edges, used, u, v, l, r);
    }
    shuffle(edges.begin(), edges.end());

    vector<long long> sizes;
    int k = rnd.next(1, 24);
    vector<long long> interesting = {1, 2, focus, max(1LL, focus - 1), focus + 1, 1000000000LL};
    for (const Edge& e : edges) {
        interesting.push_back(e.l);
        interesting.push_back(e.r);
        if (e.l > 1) {
            interesting.push_back(e.l - 1);
        }
        if (e.r < 1000000000LL) {
            interesting.push_back(e.r + 1);
        }
    }
    for (int i = 0; i < k; ++i) {
        if (rnd.next(0, 99) < 75) {
            sizes.push_back(rnd.any(interesting));
        } else {
            sizes.push_back(rnd.next(1LL, mode == 4 ? 1000000000LL : 30LL));
        }
    }
    shuffle(sizes.begin(), sizes.end());

    println(n, (int)edges.size());
    for (const Edge& e : edges) {
        println(e.u, e.v, e.l, e.r);
    }
    println(k);
    println(sizes);

    return 0;
}
