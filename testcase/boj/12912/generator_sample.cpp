#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    long long cost;
};

long long randomCost(int profile, int index) {
    if (profile == 0) {
        return rnd.next(1, 20);
    }
    if (profile == 1) {
        return rnd.next(1, 3) == 1 ? rnd.next(1, 10) : rnd.next(100, 2000);
    }
    if (profile == 2) {
        return index % 3 == 0 ? 1000000000LL : rnd.next(1, 1000);
    }
    return rnd.next(1, 1000000000);
}

void addEdge(vector<Edge>& edges, int from, int to, int profile) {
    edges.push_back({from, to, randomCost(profile, static_cast<int>(edges.size()))});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 35 : 25);
    int profile = rnd.next(0, 3);
    vector<Edge> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i - 1, i, profile);
        }
    } else if (mode == 1) {
        int center = rnd.next(0, n - 1);
        for (int v = 0; v < n; ++v) {
            if (v != center) {
                addEdge(edges, center, v, profile);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i - 1, i, profile);
        }
        for (int v = spine; v < n; ++v) {
            addEdge(edges, rnd.next(0, spine - 1), v, profile);
        }
    } else if (mode == 3) {
        int hub = rnd.next(0, n - 1);
        vector<int> tips;
        tips.push_back(hub);
        for (int v = 0; v < n; ++v) {
            if (v == hub) {
                continue;
            }
            int attach = rnd.any(tips);
            addEdge(edges, attach, v, profile);
            if (rnd.next(0, 2) != 0) {
                tips.push_back(v);
            }
        }
    } else {
        for (int v = 1; v < n; ++v) {
            int parent = rnd.next(max(0, v - 8), v - 1);
            addEdge(edges, parent, v, profile);
        }
    }

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin(), perm.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (Edge edge : edges) {
        int from = perm[edge.from];
        int to = perm[edge.to];
        if (rnd.next(0, 1)) {
            swap(from, to);
        }
        println(from, to, edge.cost);
    }

    return 0;
}
