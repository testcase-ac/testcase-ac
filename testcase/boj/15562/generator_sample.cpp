#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
    } else if (mode == 1) {
        int source = rnd.next(1, n - 1);
        for (int i = source + 1; i <= n; ++i) edges.push_back({source, i});
        int repeats = rnd.next(0, n);
        for (int i = 0; i < repeats; ++i) edges.push_back(rnd.any(edges));
    } else if (mode == 2) {
        int sink = rnd.next(2, n);
        for (int i = 1; i < sink; ++i) edges.push_back({i, sink});
        int repeats = rnd.next(0, n);
        for (int i = 0; i < repeats; ++i) edges.push_back(rnd.any(edges));
    } else if (mode == 3) {
        double density = rnd.next(0.25, 0.75);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) edges.push_back({i, j});
            }
        }
    } else if (mode == 4) {
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) {
            for (int j = split; j <= n; ++j) {
                if (rnd.next(0, 1)) edges.push_back({i, j});
            }
        }
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 2) == 0) edges.push_back({i, i + 1});
        }
    } else {
        int m = rnd.next(1, 40);
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n - 1);
            int b = rnd.next(a + 1, n);
            edges.push_back({a, b});
        }
    }

    if (edges.empty()) {
        int a = rnd.next(1, n - 1);
        edges.push_back({a, rnd.next(a + 1, n)});
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
