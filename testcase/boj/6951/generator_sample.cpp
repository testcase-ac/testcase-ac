#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int weight;
};

int nextWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{1, 2, 10, 100, 250, 500});
    }
    return rnd.next(1, 500);
}

pair<int, int> distinctPair(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) {
        ++b;
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 0 ? 12 : 20);
    int weightMode = rnd.next(0, 2);

    vector<Edge> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i, nextWeight(weightMode)});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i, nextWeight(weightMode)});
            }
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i, nextWeight(weightMode)});
        }
    } else if (mode == 3) {
        int pathLen = rnd.next(2, n);
        for (int i = 2; i <= pathLen; ++i) {
            edges.push_back({i - 1, i, nextWeight(weightMode)});
        }
        for (int i = pathLen + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, pathLen), i, nextWeight(weightMode)});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i, nextWeight(weightMode)});
        }
    }

    vector<int> label(n);
    for (int i = 0; i < n; ++i) {
        label[i] = i + 1;
    }
    if (rnd.next(0, 1)) {
        shuffle(label.begin(), label.end());
        for (Edge& edge : edges) {
            edge.u = label[edge.u - 1];
            edge.v = label[edge.v - 1];
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<pair<int, int>> packets;
    if (n >= 2) {
        packets.push_back({label[0], label[n - 1]});
    }
    if (!edges.empty()) {
        const Edge& edge = rnd.any(edges);
        packets.push_back({edge.u, edge.v});
    }
    int p = rnd.next((int)packets.size(), min(30, n * 3));
    while ((int)packets.size() < p) {
        packets.push_back(distinctPair(n));
    }
    shuffle(packets.begin(), packets.end());

    println(n, n - 1, p);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.weight);
    }
    for (const auto& packet : packets) {
        println(packet.first, packet.second);
    }

    return 0;
}
