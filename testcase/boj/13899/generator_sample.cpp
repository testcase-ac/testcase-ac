#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using Edge = tuple<int, int, long long, long long>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? 1 : rnd.next(2, 12);

    vector<long long> x(n + 1), y(n + 1);
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            x[i] = x[i - 1] + rnd.next(-20, 20);
            y[i] = y[i - 1] + rnd.next(-20, 20);
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            x[i] = rnd.next(-1000, 1000);
            y[i] = rnd.next(-1000, 1000);
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            x[i] = rnd.next(-1000000, 1000000);
            y[i] = rnd.next(-1000000, 1000000);
        }
    } else if (n > 1) {
        long long step = rnd.next(10000000, 20000000);
        for (int i = 2; i <= n; ++i) {
            x[i] = x[i - 1] + rnd.next(-1, 1) * step;
            y[i] = y[i - 1] + rnd.next(-1, 1) * step;
        }
    }

    vector<Edge> edges;
    auto addEdge = [&](int a, int b) {
        long long dx = x[b] - x[a];
        long long dy = y[b] - y[a];
        if (rnd.next(0, 1)) {
            swap(a, b);
            dx = -dx;
            dy = -dy;
        }
        edges.emplace_back(a, b, dx, dy);
    };

    if (n == 1) {
        edges.emplace_back(1, 1, 0, 0);
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            addEdge(1, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            int parent = mode == 1 ? i - 1 : rnd.next(1, i - 1);
            addEdge(parent, i);
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            candidates.emplace_back(a, b);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int targetM = rnd.next(n, min<int>(n + 12, static_cast<int>(candidates.size()) + n));
    for (int i = 0; static_cast<int>(edges.size()) < targetM; ++i) {
        if (i < static_cast<int>(candidates.size())) {
            addEdge(candidates[i].first, candidates[i].second);
        } else {
            const auto& [a, b, dx, dy] = rnd.any(edges);
            edges.emplace_back(a, b, dx, dy);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& [a, b, dx, dy] : edges) {
        println(a, b, dx, dy);
    }

    return 0;
}
