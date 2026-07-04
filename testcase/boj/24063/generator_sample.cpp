#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    long long c;
};

long long modSum(long long x, long long y, long long modValue) {
    return (x + y) % modValue;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    long long modValue = rnd.next(2, 25);
    if (mode == 4) {
        modValue = rnd.any(vector<long long>{2, 3, 4, 5, 997, 1000000000LL});
    }

    vector<int> cost(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (rnd.next(0, 3) == 0) {
            cost[i] = rnd.any(vector<int>{1, 2, 9999, 10000});
        } else {
            cost[i] = rnd.next(1, 40);
        }
    }

    vector<long long> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        value[i] = rnd.next(1LL, modValue);
    }

    vector<Edge> edges;
    auto addConsistent = [&](int a, int b) {
        edges.push_back({a, b, modSum(value[a], value[b], modValue)});
    };

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            addConsistent(rnd.next(1, i - 1), i);
        }
    } else if (mode == 1) {
        int limit = min(30, n * n);
        int target = rnd.next(n, limit);
        for (int i = 0; i < target; ++i) {
            addConsistent(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            addConsistent(i, i);
        }
        int extra = rnd.next(1, n);
        for (int i = 0; i < extra; ++i) {
            addConsistent(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            addConsistent(i, i + 1);
        }
        addConsistent(n, 1);
        int extra = rnd.next(1, n);
        for (int i = 0; i < extra; ++i) {
            addConsistent(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 4) {
        int target = rnd.next(1, min(12, n * n));
        for (int i = 0; i < target; ++i) {
            addConsistent(rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        int target = rnd.next(2, min(18, n * n));
        for (int i = 0; i < target; ++i) {
            addConsistent(rnd.next(1, n), rnd.next(1, n));
        }
        int id = rnd.next(0, int(edges.size()) - 1);
        edges[id].c = (edges[id].c + rnd.next(1LL, modValue - 1)) % modValue;
    }

    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()), modValue);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << cost[i];
    }
    cout << '\n';
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c);
    }

    return 0;
}
