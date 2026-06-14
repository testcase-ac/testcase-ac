#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int s;
    int t;
    int c;
};

static void addEdge(vector<Edge>& edges, int s, int t, int c) {
    edges.push_back({s, t, c});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<int> label(n);
    for (int i = 0; i < n; ++i) {
        label[i] = i + 1;
    }
    shuffle(label.begin(), label.end());

    vector<Edge> edges;

    if (mode == 0) {
        int chainLength = rnd.next(2, n);
        for (int i = 0; i + 1 < chainLength; ++i) {
            addEdge(edges, label[i], label[i + 1], rnd.next(1, 100));
        }

        int extra = rnd.next(0, min(10, n));
        for (int it = 0; it < extra; ++it) {
            int a = rnd.next(0, n - 2);
            int b = rnd.next(a + 1, n - 1);
            addEdge(edges, label[a], label[b], rnd.next(1, 100));
        }
    } else if (mode == 1) {
        vector<int> layer(n);
        int layers = rnd.next(2, min(5, n));
        for (int i = 0; i < n; ++i) {
            layer[i] = rnd.next(0, layers - 1);
        }
        layer[0] = 0;
        layer[n - 1] = layers - 1;

        double density = rnd.next(0.30, 0.75);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (layer[i] < layer[j] && rnd.next() < density) {
                    addEdge(edges, label[i], label[j], rnd.next(1, 100));
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i + 1 < n; ++i) {
            addEdge(edges, label[i], label[i + 1], rnd.next(1, 100));
            if (rnd.next(0, 1)) {
                addEdge(edges, label[i], label[i + 1], rnd.next(1, 100));
            }
        }

        int duplicates = rnd.next(1, min(12, n * 2));
        for (int it = 0; it < duplicates; ++it) {
            int a = rnd.next(0, n - 2);
            int b = rnd.next(a + 1, n - 1);
            addEdge(edges, label[a], label[b], rnd.next(1, 100));
        }
    } else if (mode == 3) {
        double density = rnd.next(0.10, 0.45);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) {
                    addEdge(edges, label[i], label[j], rnd.next(1, 100));
                }
            }
        }
    } else {
        int sources = rnd.next(1, min(4, n - 1));
        int sinksBegin = max(sources, n - rnd.next(1, min(4, n - sources)));
        for (int i = 0; i < sources; ++i) {
            for (int j = sources; j < n; ++j) {
                if (rnd.next(0, 2) > 0) {
                    addEdge(edges, label[i], label[j], rnd.next(1, 100));
                }
            }
        }
        for (int i = sources; i < sinksBegin; ++i) {
            for (int j = max(i + 1, sinksBegin); j < n; ++j) {
                if (rnd.next(0, 1)) {
                    addEdge(edges, label[i], label[j], rnd.next(1, 100));
                }
            }
        }
    }

    if (edges.empty()) {
        addEdge(edges, label[0], label[1], rnd.next(1, 100));
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.s, edge.t, edge.c);
    }

    return 0;
}
