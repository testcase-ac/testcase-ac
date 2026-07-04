#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, int a, int b) {
    if (a == b) return;
    if (rnd.next(2)) swap(a, b);
    edges.push_back({a, b});
}

void addRandomTree(vector<Edge>& edges, int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int parent = rnd.next(0, i - 1);
        addEdge(edges, order[i], order[parent]);
    }
}

void addPath(vector<Edge>& edges, int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        addEdge(edges, order[i - 1], order[i]);
    }
}

void addStar(vector<Edge>& edges, int n) {
    int center = rnd.next(0, n - 1);
    for (int node = 0; node < n; ++node) {
        if (node != center) addEdge(edges, center, node);
    }
}

vector<Edge> allSimpleEdges(int n) {
    vector<Edge> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 10 : 14);
    vector<Edge> edges;

    if (mode == 0) {
        addRandomTree(edges, n);
    } else if (mode == 1) {
        addPath(edges, n);
        int extra = rnd.next(1, min(8, n));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 2);
            if (b >= a) ++b;
            addEdge(edges, a, b);
        }
    } else if (mode == 2) {
        addStar(edges, n);
        int extra = rnd.next(0, min(6, n * (n - 1) / 2));
        for (auto [a, b] : allSimpleEdges(n)) {
            if (extra == 0) break;
            addEdge(edges, a, b);
            --extra;
        }
    } else if (mode == 3) {
        addRandomTree(edges, n);
        vector<Edge> base = edges;
        int copies = rnd.next(1, 4);
        for (int i = 0; i < copies; ++i) {
            auto [a, b] = rnd.any(base);
            addEdge(edges, a, b);
        }
        int extra = rnd.next(1, min(8, n));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 2);
            if (b >= a) ++b;
            addEdge(edges, a, b);
        }
    } else {
        n = rnd.next(5, 10);
        int target = rnd.next(n - 1, min(30, n * (n - 1) / 2));
        addRandomTree(edges, n);
        for (auto [a, b] : allSimpleEdges(n)) {
            if ((int)edges.size() >= target) break;
            addEdge(edges, a, b);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
