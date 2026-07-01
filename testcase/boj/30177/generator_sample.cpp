#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    edges.push_back({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 1; v < n; ++v) {
            addEdge(edges, v, v + 1);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                addEdge(edges, center, v);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, max(2, n / 2));
        for (int v = 1; v < spine; ++v) {
            addEdge(edges, v, v + 1);
        }
        for (int v = spine + 1; v <= n; ++v) {
            addEdge(edges, v, rnd.next(1, spine));
        }
    } else if (mode == 3) {
        int hubs = rnd.next(2, min(n - 1, 6));
        for (int v = 1; v < hubs; ++v) {
            addEdge(edges, v, v + 1);
        }
        for (int v = hubs + 1; v <= n; ++v) {
            int hub = rnd.next(1, hubs);
            if (rnd.next(0, 3) == 0) {
                hub = rnd.next(max(1, hubs - 1), hubs);
            }
            addEdge(edges, hub, v);
        }
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) {
            int parent = max(1, v / 2 + rnd.next(-1, 1));
            parent = min(parent, v - 1);
            addEdge(edges, parent, v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent;
            if (rnd.next(0, 4) == 0) {
                parent = rnd.next(max(1, v - 4), v - 1);
            } else {
                parent = rnd.next(1, v - 1);
            }
            addEdge(edges, parent, v);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
