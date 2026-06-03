#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

static vector<int> shuffledVertices(int n) {
    vector<int> vertices;
    for (int i = 1; i <= n; ++i) vertices.push_back(i);
    shuffle(vertices.begin(), vertices.end());
    return vertices;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int x = rnd.next(1, n);
    set<pair<int, int>> edges;

    if (mode == 0) {
        vector<int> v = shuffledVertices(n);
        for (int i = 0; i < n; ++i) {
            if (v[i] == x) {
                swap(v[i], v[rnd.next(0, n - 1)]);
                break;
            }
        }
        for (int i = 1; i < n; ++i) addEdge(edges, v[i - 1], v[i]);
    } else if (mode == 1) {
        for (int v = 1; v <= n; ++v) {
            if (v != x && rnd.next(0, 1)) addEdge(edges, x, v);
        }
    } else if (mode == 2) {
        vector<int> others;
        for (int v = 1; v <= n; ++v) {
            if (v != x) others.push_back(v);
        }
        shuffle(others.begin(), others.end());
        if (others.size() == 1) {
            addEdge(edges, x, others[0]);
        } else {
            int cycleSize = rnd.next(2, min<int>(4, others.size()));
            addEdge(edges, x, others[0]);
            for (int i = 1; i < cycleSize; ++i) addEdge(edges, others[i - 1], others[i]);
            addEdge(edges, others[cycleSize - 1], x);
            for (int i = cycleSize; i < (int)others.size(); ++i) {
                if (rnd.next(0, 2) > 0) {
                    int to = others[rnd.next(0, i - 1)];
                    addEdge(edges, others[i], to);
                }
            }
        }
    } else if (mode == 3) {
        vector<int> v = shuffledVertices(n);
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) addEdge(edges, v[i - 1], v[i]);
        for (int i = split + 1; i < n; ++i) addEdge(edges, v[i - 1], v[i]);
        if (rnd.next(0, 1)) {
            int y = rnd.next(1, n - 1);
            if (y >= x) ++y;
            addEdge(edges, x, y);
        }
    } else {
        double density = rnd.next(0.15, 0.45);
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (rnd.next() < density) addEdge(edges, a, b);
            }
        }
    }

    while (edges.empty()) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a != b) addEdge(edges, a, b);
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(n, (int)output.size());
    for (auto [a, b] : output) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }
    println(x);

    return 0;
}
