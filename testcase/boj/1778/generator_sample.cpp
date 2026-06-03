#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(vector<pair<int, int>>& edges, set<pair<int, int>>& used, int a, int b) {
    if (a == b) return;
    auto edge = minmax(a, b);
    if (used.insert(edge).second) edges.push_back({a, b});
}

static vector<pair<int, int>> buildCase(int n, int mode) {
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        return edges;
    }

    if (mode == 1) {
        int len = rnd.next(2, n);
        for (int i = 2; i <= len; ++i) addEdge(edges, used, i - 1, i);
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center && rnd.next(0, 3) != 0) addEdge(edges, used, center, v);
        }
    } else if (mode == 3) {
        int limit = rnd.next(2, n);
        for (int i = 1; i <= limit; ++i) {
            for (int j = i + 1; j <= limit; ++j) {
                if (rnd.next(0, 1)) addEdge(edges, used, i, j);
            }
        }
    } else {
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());

        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            int size = min(remaining, rnd.next(1, min(5, remaining)));
            if (size >= 2) {
                for (int i = 1; i < size; ++i) addEdge(edges, used, vertices[pos], vertices[pos + i]);
                if (size >= 3 && rnd.next(0, 1)) addEdge(edges, used, vertices[pos + 1], vertices[pos + 2]);
            }
            pos += size;
        }
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 5);
    for (int tc = 0; tc < testCount; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 8);
        } else if (mode == 3) {
            n = rnd.next(3, 12);
        } else {
            n = rnd.next(2, 15);
        }

        vector<pair<int, int>> edges = buildCase(n, mode);
        println(n, static_cast<int>(edges.size()));
        for (auto [a, b] : edges) println(a, b);
    }

    println(0, 0);
    return 0;
}
