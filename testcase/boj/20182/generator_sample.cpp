#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, w});
    }
}

static void relabel(vector<Edge>& edges, int& a, int& b, int n) {
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) p[i] = i;
    shuffle(p.begin() + 1, p.end());

    a = p[a];
    b = p[b];
    for (auto& e : edges) {
        e.u = p[e.u];
        e.v = p[e.v];
        if (rnd.next(2)) swap(e.u, e.v);
    }
    shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = 0;
    int a = 1;
    int b = 2;
    int c = 1;
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(4, 10);
        a = 1;
        b = n;
        c = rnd.next(1, 40);

        int leftSize = rnd.next(2, n - 2);
        for (int i = 1; i < leftSize; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 20));
        }
        for (int i = leftSize + 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 20));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        a = 1;
        b = n;

        int sum = 0;
        for (int i = 1; i < n; ++i) {
            int w = rnd.next(1, 20);
            sum += w;
            addEdge(edges, used, i, i + 1, w);
        }

        int delta = rnd.next(-5, 5);
        c = max(1, min(2000000, sum + delta));
    } else if (mode == 2) {
        int len1 = rnd.next(2, 5);
        int len2 = rnd.next(2, 5);
        n = 2 + (len1 - 1) + (len2 - 1) + rnd.next(0, 3);
        a = 1;
        b = 2;

        auto makePath = [&](int len, int& nextNode, int low, int high) {
            int prev = a;
            int sum = 0;
            for (int i = 1; i <= len; ++i) {
                int cur = (i == len ? b : nextNode++);
                int w = rnd.next(low, high);
                sum += w;
                addEdge(edges, used, prev, cur, w);
                prev = cur;
            }
            return sum;
        };

        int nextNode = 3;
        int cheapSum = makePath(len1, nextNode, 1, 7);
        int costlySum = makePath(len2, nextNode, 8, 20);
        c = rnd.any(vector<int>{max(1, cheapSum - rnd.next(0, 3)), cheapSum, min(2000000, costlySum)});
    } else {
        n = rnd.next(5, 13);
        a = 1;
        b = n;
        double density = rnd.next(0.25, 0.75);

        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) {
                    int w = rnd.next(1, 20);
                    addEdge(edges, used, u, v, w);
                }
            }
        }
        if (edges.empty()) addEdge(edges, used, a, b, rnd.next(1, 20));
        c = rnd.next(1, min(2000000, 20 * max(1, n - 1)));
    }

    while (edges.empty()) {
        addEdge(edges, used, a, b, rnd.next(1, 20));
    }

    relabel(edges, a, b, n);

    println(n, int(edges.size()), a, b, c);
    for (const auto& e : edges) {
        println(e.u, e.v, e.w);
    }

    return 0;
}
