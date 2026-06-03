#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, int u, int v) {
    if (rnd.next(2)) swap(u, v);
    edges.emplace_back(u, v);
}

void addPath(vector<Edge>& edges, const vector<int>& nodes) {
    for (int i = 1; i < int(nodes.size()); ++i) {
        addEdge(edges, nodes[i - 1], nodes[i]);
    }
}

void addCycle(vector<Edge>& edges, const vector<int>& nodes) {
    addPath(edges, nodes);
    addEdge(edges, nodes.back(), nodes.front());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 18);
    if (mode == 1 && n == 2) n = 3;
    vector<Edge> edges;

    if (mode == 0) {
        vector<int> left, right;
        for (int i = 1; i <= n; ++i) {
            (rnd.next(2) ? left : right).push_back(i);
        }
        if (left.empty()) {
            left.push_back(right.back());
            right.pop_back();
        }
        if (right.empty()) {
            right.push_back(left.back());
            left.pop_back();
        }

        int m = rnd.next(1, min(35, int(left.size() * right.size() + 8)));
        for (int i = 0; i < m; ++i) {
            addEdge(edges, rnd.any(left), rnd.any(right));
        }
    } else if (mode == 1) {
        int len = rnd.next(1, min(4, (n - 1) / 2)) * 2 + 1;
        vector<int> cycle;
        for (int i = 1; i <= len; ++i) cycle.push_back(i);
        shuffle(cycle.begin(), cycle.end());
        addCycle(edges, cycle);

        int extra = rnd.next(0, min(12, n + 3));
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(edges, u, v);
        }
    } else if (mode == 2) {
        int baseEdges = rnd.next(1, min(6, n * (n - 1) / 2));
        vector<Edge> base;
        for (int i = 0; i < baseEdges; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            base.emplace_back(u, v);
        }

        int m = rnd.next(baseEdges, min(40, baseEdges * 6));
        for (int i = 0; i < m; ++i) {
            auto edge = rnd.any(base);
            addEdge(edges, edge.first, edge.second);
        }
    } else {
        int components = rnd.next(2, min(5, n));
        int nextNode = 1;
        for (int c = 0; c < components && nextNode <= n; ++c) {
            int remaining = n - nextNode + 1;
            int size = (c == components - 1) ? remaining : rnd.next(1, remaining - (components - c - 1));
            vector<int> comp;
            for (int i = 0; i < size; ++i) comp.push_back(nextNode++);
            if (comp.size() == 1) continue;

            shuffle(comp.begin(), comp.end());
            if (comp.size() >= 3 && rnd.next(3) == 0) {
                int len = rnd.next(1, int((comp.size() - 1) / 2)) * 2 + 1;
                vector<int> cycle(comp.begin(), comp.begin() + len);
                addCycle(edges, cycle);
            } else {
                addPath(edges, comp);
            }
        }
    }

    if (edges.empty()) {
        addEdge(edges, 1, 2);
    }

    shuffle(edges.begin(), edges.end());
    println(n, int(edges.size()));
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
