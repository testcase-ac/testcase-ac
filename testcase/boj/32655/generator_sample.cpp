#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
using Edge = tuple<int, int, long long>;

void addEdge(vector<Edge>& edges, set<pair<int, int>>& seen, int a, int b,
             long long c) {
    if (a > b) swap(a, b);
    if (a == b || !seen.insert({a, b}).second) return;
    edges.emplace_back(a, b, c);
}

long long nearK(long long k) {
    if (rnd.next(3) == 0) return rnd.next(1LL, 20LL);
    long long delta = rnd.next(-2LL, 2LL);
    return min(1000000000LL, max(1LL, k + delta));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 12);
    long long k;
    if (mode == 0) {
        k = rnd.next(1LL, 5LL);
    } else if (mode == 1) {
        k = rnd.next(8LL, 30LL);
    } else if (mode == 2) {
        k = rnd.next(100000000LL, 1000000000LL);
    } else {
        k = rnd.next(2LL, 50LL);
    }

    vector<Edge> edges;
    set<pair<int, int>> seen;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, seen, v - 1, v, nearK(k));
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, seen, 1, v, rnd.next(1LL, min(1000000000LL, 3LL * k)));
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, seen, rnd.next(1, v - 1), v, nearK(k));
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            long long w = (v % 2 == 0) ? 1LL : nearK(k);
            addEdge(edges, seen, rnd.next(1, v - 1), v, w);
        }
    } else {
        vector<int> order;
        for (int i = 1; i <= n; ++i) order.push_back(i);
        shuffle(order.begin() + 1, order.end());
        for (int i = 0; i + 1 < n; ++i) {
            addEdge(edges, seen, order[i], order[i + 1], nearK(k));
        }
    }

    int maxEdges = n * (n - 1) / 2;
    int target = rnd.next(max(3, n - 1), min(maxEdges, n + rnd.next(0, n)));

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!seen.count({a, b})) candidates.emplace_back(a, b);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [a, b] : candidates) {
        long long w;
        int weightMode = rnd.next(4);
        if (weightMode == 0) {
            w = 1;
        } else if (weightMode == 1) {
            w = nearK(k);
        } else if (weightMode == 2) {
            w = rnd.next(1LL, min(1000000000LL, max(1LL, 3LL * k)));
        } else {
            w = rnd.next(1LL, 1000000000LL);
        }
        addEdge(edges, seen, a, b, w);
        if ((int)edges.size() == target) break;
    }

    for (auto& [a, b, c] : edges) {
        if (rnd.next(2)) swap(a, b);
    }
    shuffle(edges.begin(), edges.end());

    vector<int> exits;
    for (int v = 1; v <= n; ++v) exits.push_back(v);
    shuffle(exits.begin(), exits.end());
    int x;
    if (mode == 4) {
        x = n;
    } else {
        x = rnd.next(1, n);
    }
    exits.resize(x);
    if (rnd.next(2) && find(exits.begin(), exits.end(), 1) == exits.end()) {
        exits[rnd.next(x)] = 1;
    }

    println(n, (int)edges.size(), k);
    for (auto [a, b, c] : edges) {
        println(a, b, c);
    }
    println(x);
    println(exits);

    return 0;
}
