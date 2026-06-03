#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenarios = rnd.next(1, 5);
    println(scenarios);

    for (int scenario = 0; scenario < scenarios; ++scenario) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 12);
        if (mode == 5) n = rnd.any(vector<int>{50, 1000, 1000000});

        vector<pair<int, int>> edges;

        if (mode == 0) {
            int k = rnd.next(1, 4);
            for (int i = 0; i < k; ++i) {
                int v = rnd.next(0, n - 1);
                edges.push_back({v, v});
            }
        } else if (mode == 1) {
            for (int i = 0; i + 1 < n; ++i) edges.push_back({i, i + 1});
        } else if (mode == 2) {
            int center = rnd.next(0, n - 1);
            for (int i = 0; i < n; ++i) {
                if (i != center) edges.push_back({center, i});
            }
        } else if (mode == 3) {
            int split = rnd.next(1, max(1, n - 1));
            for (int i = 0; i + 1 < split; ++i) edges.push_back({i, i + 1});
            for (int i = split; i + 1 < n; ++i) edges.push_back({i, i + 1});
        } else if (mode == 4) {
            int baseEdges = rnd.next(1, max(1, n + 2));
            for (int i = 0; i < baseEdges; ++i) {
                int a = rnd.next(0, n - 1);
                int b = rnd.next(0, n - 1);
                edges.push_back({a, b});
                if (rnd.next(0, 2) == 0) edges.push_back({a, b});
            }
        } else {
            int active = rnd.next(2, 10);
            for (int i = 0; i + 1 < active; ++i) edges.push_back({i, i + 1});
            if (rnd.next(0, 1) == 1) edges.push_back({n - 1, n - 1});
        }

        if (edges.empty()) {
            int v = rnd.next(0, n - 1);
            edges.push_back({v, v});
        }
        shuffle(edges.begin(), edges.end());

        int m = rnd.next(1, 12);
        vector<pair<int, int>> queries;
        for (int i = 0; i < m; ++i) {
            int kind = rnd.next(0, 4);
            int a;
            int b;
            if (kind == 0) {
                a = b = rnd.next(0, n - 1);
            } else if (kind == 1 && n > 1) {
                a = rnd.next(0, n / 2);
                b = rnd.next((n + 1) / 2, n - 1);
            } else if (kind == 2 && !edges.empty()) {
                auto edge = rnd.any(edges);
                a = edge.first;
                b = edge.second;
            } else {
                a = rnd.next(0, n - 1);
                b = rnd.next(0, n - 1);
            }
            queries.push_back({a, b});
        }

        println(n);
        println(static_cast<int>(edges.size()));
        for (auto edge : edges) println(edge.first, edge.second);
        println(static_cast<int>(queries.size()));
        for (auto query : queries) println(query.first, query.second);
    }

    return 0;
}
