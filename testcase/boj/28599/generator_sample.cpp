#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 12);
    int maxEdges = n * (n - 1) / 2;
    int mode = rnd.next(4);

    vector<tuple<int, int, long long>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b, long long c) {
        if (a > b) swap(a, b);
        if (a == b || used.count({a, b})) return false;
        used.insert({a, b});
        edges.emplace_back(a, b, c);
        return true;
    };

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            addEdge(1, v, rnd.next(1, 20));
        }
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) {
            addEdge(v, v + 1, rnd.next(1, 25));
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            addEdge(rnd.next(1, v - 1), v, rnd.next(1, 30));
        }
    }

    int targetEdges = rnd.next(max(2, (int)edges.size()), min(maxEdges, (int)edges.size() + rnd.next(0, n)));
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= targetEdges) break;
        long long c;
        if (rnd.next(5) == 0) {
            c = rnd.next(100000000, 1000000000);
        } else {
            c = rnd.next(1, 50);
        }
        addEdge(a, b, c);
    }

    shuffle(edges.begin(), edges.end());

    int s = rnd.next(2, 16);
    int k = rnd.next(2, s);

    println(n, (int)edges.size(), k);
    for (auto [a, b, c] : edges) {
        if (rnd.next(2)) swap(a, b);
        println(a, b, c);
    }

    println(s);
    for (int i = 0; i < s; ++i) {
        int v;
        if (i == 0 && rnd.next(2)) {
            v = 1;
        } else if (mode == 3 && rnd.next(3) == 0) {
            v = n;
        } else {
            v = rnd.next(1, n);
        }

        long long h = rnd.next(1, 60);
        long long t = rnd.next(1, 30);
        if (rnd.next(8) == 0) h = rnd.next(100000000, 1000000000);
        if (rnd.next(8) == 0) t = rnd.next(100000000, 1000000000);
        println(v, h, t);
    }

    long long target = rnd.next(1, 80);
    if (rnd.next(6) == 0) target = rnd.next(1000000, 1000000000);
    println(target);

    return 0;
}
