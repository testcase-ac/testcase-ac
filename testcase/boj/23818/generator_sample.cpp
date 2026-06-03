#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int t;
    int a;
    int b;
};

pair<int, int> distinctPair(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;
    return {a, b};
}

void addRandomQueries(vector<pair<int, int>>& queries, int n, int target) {
    while ((int)queries.size() < target) queries.push_back(distinctPair(n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<Edge> edges;
    vector<pair<int, int>> queries;

    if (mode == 0) {
        n = rnd.next(2, 10);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        for (int i = 1; i < n; ++i) edges.push_back({rnd.next(0, 1), i, i + 1});
        queries.push_back({1, n});
        queries.push_back({1, 2});
        queries.push_back({n / 2, n});
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        int t1 = rnd.next(0, 1);
        int t2 = rnd.next(0, 1);
        edges.push_back({t1, 1, 2});
        edges.push_back({t2, 2, 3});
        edges.push_back({1 - (t1 ^ t2), 1, 3});
        queries.push_back({1, 3});
        queries.push_back({1, 2});
        if (n > 3) queries.push_back({1, n});
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) edges.push_back({rnd.next(0, 1), i, i + 1});
        for (int i = split + 1; i < n; ++i) edges.push_back({rnd.next(0, 1), i, i + 1});
        queries.push_back({1, split});
        queries.push_back({split, n});
        queries.push_back({1, n});
    } else if (mode == 4) {
        n = rnd.next(3, 8);
        auto [a, b] = distinctPair(n);
        edges.push_back({0, a, b});
        edges.push_back({1, a, b});
        if (rnd.next(0, 1)) edges.push_back({rnd.next(0, 1), a, b});
        queries.push_back({a, b});
    } else {
        n = rnd.next(6, 14);
        double density = rnd.next(0.15, 0.45);
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (rnd.next() < density) edges.push_back({rnd.next(0, 1), a, b});
            }
        }
        shuffle(edges.begin(), edges.end());
        int keep = rnd.next(0, min((int)edges.size(), 22));
        edges.resize(keep);
    }

    shuffle(edges.begin(), edges.end());
    int queryCount = rnd.next(max(1, (int)queries.size()), max(1, (int)queries.size()) + 12);
    addRandomQueries(queries, n, queryCount);
    shuffle(queries.begin(), queries.end());

    println(n, (int)edges.size(), (int)queries.size());
    for (const Edge& e : edges) println(e.t, e.a, e.b);
    for (const auto& q : queries) println(q.first, q.second);

    return 0;
}
