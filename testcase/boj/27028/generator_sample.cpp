#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int length;
    char direction;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(4);
    vector<Edge> edges;

    for (int v = 2; v <= n; ++v) {
        int parent;
        if (mode == 0) {
            parent = v - 1;
        } else if (mode == 1) {
            parent = 1;
        } else if (mode == 2) {
            parent = max(1, v - rnd.next(1, min(v - 1, 3)));
        } else {
            parent = rnd.next(1, v - 1);
        }

        int length;
        if (rnd.next(5) == 0) {
            length = rnd.any(vector<int>{1, 2, 999, 1000});
        } else {
            length = rnd.next(1, 40);
        }

        char direction = rnd.any(string("NESW"));
        int u = parent;
        int w = v;
        if (rnd.next(2) == 0) {
            swap(u, w);
        }
        edges.push_back({u, w, length, direction});
    }

    shuffle(edges.begin(), edges.end());

    int k = rnd.next(1, min(30, n * 3));
    vector<pair<int, int>> queries;
    queries.reserve(k);

    for (int i = 0; i < k; ++i) {
        int queryMode = rnd.next(5);
        int a;
        int b;
        if (queryMode == 0) {
            a = b = rnd.next(1, n);
        } else if (queryMode == 1) {
            a = 1;
            b = rnd.next(1, n);
        } else if (queryMode == 2) {
            a = rnd.next(max(1, n - 3), n);
            b = rnd.next(max(1, n - 3), n);
        } else {
            a = rnd.next(1, n);
            b = rnd.next(1, n);
        }
        queries.push_back({a, b});
    }

    println(n, n - 1);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.length, edge.direction);
    }
    println(k);
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
