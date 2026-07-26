#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static int randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(-5, 5);
    }
    if (mode == 1) {
        return rnd.next(0, 5);
    }
    if (mode == 2) {
        return rnd.next(0, 3) == 0 ? rnd.next(0, 5) : rnd.next(-10000000, -1000000);
    }
    if (mode == 3) {
        const int special[] = {-10000000, -1, 0, 1, 10000000};
        return special[rnd.next(0, 4)];
    }
    return rnd.next(-10000000, 10000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int shape = rnd.next(0, 4);
    int weightMode = rnd.next(0, 4);

    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        int parent;
        if (shape == 0) {
            parent = v - 1;
        } else if (shape == 1) {
            parent = 0;
        } else if (shape == 2) {
            parent = (v - 1) / 2;
        } else if (shape == 3) {
            parent = rnd.next(0, v - 1);
        } else {
            parent = v == 1 ? 0 : rnd.next(0, 1);
        }

        Edge edge{label[parent], label[v], randomWeight(weightMode)};
        if (rnd.next(0, 1)) {
            swap(edge.u, edge.v);
        }
        edges.push_back(edge);
    }

    shuffle(edges.begin(), edges.end());
    println(n);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
}
