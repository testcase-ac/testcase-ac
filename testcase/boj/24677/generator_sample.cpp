#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void addCycle(vector<pair<int, int>>& edges, const vector<int>& nodes) {
    for (int i = 0; i < int(nodes.size()); ++i) {
        edges.push_back({nodes[i], nodes[(i + 1) % int(nodes.size())]});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 4);
        int q = rnd.next(1, 8);
        for (int i = 0; i < q; ++i) {
            int v = rnd.next(1, n);
            edges.push_back({v, v});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        vector<int> nodes;
        for (int i = 1; i <= n; ++i) nodes.push_back(i);
        shuffle(nodes.begin(), nodes.end());
        int len = rnd.next(2, n);
        nodes.resize(len);
        addCycle(edges, nodes);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        int len = rnd.next(2, n);
        for (int i = 1; i < len; ++i) edges.push_back({i, i + 1});
        edges.push_back({rnd.next(1, len), rnd.next(1, len)});
        if (rnd.next(0, 1)) edges.push_back({1, len});
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        pair<int, int> repeated = {rnd.next(1, n), rnd.next(1, n)};
        int q = rnd.next(2, 12);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 2) == 0) {
                edges.push_back(repeated);
            } else {
                edges.push_back({rnd.next(1, n), rnd.next(1, n)});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(8, 16);
        int q = rnd.next(n, min(60, n * n));
        for (int i = 0; i < q; ++i) {
            edges.push_back({rnd.next(1, n), rnd.next(1, n)});
        }
    } else {
        n = rnd.next(6, 14);
        int components = rnd.next(2, min(4, n));
        int nextNode = 1;
        for (int c = 0; c < components && nextNode <= n; ++c) {
            int remaining = n - nextNode + 1;
            int len = (c + 1 == components) ? remaining : rnd.next(1, remaining - (components - c - 1));
            if (len == 1) {
                edges.push_back({nextNode, nextNode});
            } else {
                vector<int> nodes;
                for (int i = 0; i < len; ++i) nodes.push_back(nextNode + i);
                addCycle(edges, nodes);
            }
            nextNode += len;
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (auto [x, y] : edges) {
        println(x, y);
    }

    return 0;
}
