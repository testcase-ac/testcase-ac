#include "testlib.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int to;
    long long dx;
    long long dy;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(n, 1000000, "M");
    inf.readEoln();

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        long long dx = inf.readLong(-100000000LL, 100000000LL, "dx_i");
        inf.readSpace();
        long long dy = inf.readLong(-100000000LL, 100000000LL, "dy_i");
        inf.readEoln();

        // CHECK: The statement does not explicitly forbid a_i == b_i.
        graph[a - 1].push_back({b - 1, dx, dy});
        graph[b - 1].push_back({a - 1, -dx, -dy});
    }

    vector<int> seen(n, 0);
    vector<long long> x(n, 0), y(n, 0);
    queue<int> q;
    seen[0] = 1;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const Edge& e : graph[v]) {
            long long nx = x[v] + e.dx;
            long long ny = y[v] + e.dy;
            if (!seen[e.to]) {
                seen[e.to] = 1;
                x[e.to] = nx;
                y[e.to] = ny;
                q.push(e.to);
            } else {
                ensuref(x[e.to] == nx && y[e.to] == ny,
                        "inconsistent constraint reaching base %d", e.to + 1);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ensuref(seen[i], "base %d is not determined by the interrogations", i + 1);
    }

    auto [min_x, max_x] = minmax_element(x.begin(), x.end());
    auto [min_y, max_y] = minmax_element(y.begin(), y.end());
    ensuref(*max_x - *min_x < 100000000LL, "x-coordinate span does not fit the map");
    ensuref(*max_y - *min_y < 100000000LL, "y-coordinate span does not fit the map");

    inf.readEof();
}
