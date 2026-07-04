#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addPath(vector<Edge>& edges, int first, int length) {
    for (int i = 0; i + 1 < length; ++i) {
        edges.push_back({first + i, first + i + 1});
    }
}

vector<Edge> makeTree(int n, int mode) {
    vector<Edge> edges;
    if (n == 1) {
        return edges;
    }

    if (mode == 0) {
        addPath(edges, 1, n);
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v});
        }
    } else if (mode == 2) {
        int pathLength = rnd.next(2, n);
        addPath(edges, 1, pathLength);
        for (int v = pathLength + 1; v <= n; ++v) {
            edges.push_back({pathLength, v});
        }
    } else if (mode == 3) {
        edges.push_back({1, 2});
        for (int v = 3; v <= n; ++v) {
            edges.push_back({rnd.next(0, 1) == 0 ? 1 : 2, v});
        }
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int bias = rnd.next(-2, 2);
            int parent = rnd.wnext(v - 1, bias) + 1;
            edges.push_back({parent, v});
        }
    }

    return edges;
}

int chooseN(int mode) {
    if (mode == 0) {
        return rnd.next(1, 18);
    }
    if (mode <= 4) {
        return rnd.next(2, 35);
    }
    return rnd.next(8, 80);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = chooseN(mode);
    vector<Edge> edges = makeTree(n, mode);

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (Edge& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (const Edge& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
