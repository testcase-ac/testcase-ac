#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

int randomWeight() {
    if (rnd.next(4) == 0) {
        return rnd.next(900, 1000);
    }
    return rnd.next(1, 25);
}

vector<int> relabelEdges(vector<Edge>& edges, int n, int& root) {
    vector<int> label(n + 1);
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    for (int i = 1; i <= n; ++i) {
        label[i] = nodes[i - 1];
    }

    for (Edge& edge : edges) {
        edge.a = label[edge.a];
        edge.b = label[edge.b];
        if (rnd.next(2) == 0) {
            swap(edge.a, edge.b);
        }
    }
    root = label[root];
    return label;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<Edge> edges;
    int n = 1;
    int root = 1;

    if (mode == 0) {
        n = rnd.next(1, 2);
        if (n == 2) {
            edges.push_back({1, 2, randomWeight()});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        root = rnd.next(1, n);
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1, randomWeight()});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 13);
        root = 1;
        int nextNode = 2;
        int branches = rnd.next(2, min(5, n - 1));
        for (int branch = 0; branch < branches; ++branch) {
            edges.push_back({root, nextNode++, randomWeight()});
        }
        while (nextNode <= n) {
            int parent = rnd.next(2, nextNode - 1);
            edges.push_back({parent, nextNode++, randomWeight()});
        }
    } else if (mode == 3) {
        int stemLength = rnd.next(1, 5);
        int branches = rnd.next(2, 4);
        n = min(14, 1 + stemLength + branches + rnd.next(0, 4));
        root = 1;

        for (int i = 1; i <= stemLength; ++i) {
            edges.push_back({i, i + 1, randomWeight()});
        }

        int giga = stemLength + 1;
        int nextNode = giga + 1;
        for (int branch = 0; branch < branches && nextNode <= n; ++branch) {
            edges.push_back({giga, nextNode++, randomWeight()});
        }
        while (nextNode <= n) {
            int parent = rnd.next(giga + 1, nextNode - 1);
            edges.push_back({parent, nextNode++, randomWeight()});
        }
    } else {
        n = rnd.next(5, 14);
        root = rnd.next(1, n);
        for (int node = 2; node <= n; ++node) {
            int parent = rnd.next(1, node - 1);
            edges.push_back({parent, node, randomWeight()});
        }
    }

    relabelEdges(edges, n, root);
    shuffle(edges.begin(), edges.end());

    println(n, root);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.w);
    }

    return 0;
}
