#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int v = (mode == 0 ? 1 : rnd.next(2, 15));

    vector<pair<int, int>> candidates;
    for (int i = 1; i <= v; ++i) {
        for (int j = i + 1; j <= v; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    vector<pair<pair<int, int>, int>> edges;
    auto addEdge = [&](int a, int b, int w) {
        edges.push_back({{a, b}, w});
    };

    if (mode == 0) {
        // Single-vertex case accepted by the validator.
    } else if (mode == 1) {
        for (int i = 1; i < v; ++i) {
            addEdge(i, i + 1, rnd.next(1, 30));
        }
    } else if (mode == 2) {
        int componentEnd = rnd.next(1, v - 1);
        for (int i = 1; i < componentEnd; ++i) {
            addEdge(i, i + 1, rnd.next(1, 50));
        }
        for (int i = componentEnd + 1; i < v; ++i) {
            addEdge(i, i + 1, rnd.next(1, 50));
        }
    } else if (mode == 3) {
        int take = rnd.next(0, min<int>(candidates.size(), v * 2));
        for (int i = 0; i < take; ++i) {
            addEdge(candidates[i].first, candidates[i].second, rnd.next(1, 100));
        }
    } else if (mode == 4) {
        for (int i = 2; i <= v; ++i) {
            addEdge(1, i, rnd.next(1, 20));
        }
        int extra = rnd.next(0, min<int>(candidates.size(), v));
        for (int i = 0; i < extra; ++i) {
            addEdge(candidates[i].first, candidates[i].second, rnd.next(1, 100000));
        }
    } else {
        int take = rnd.next(0, min<int>(candidates.size(), v * 3));
        for (int i = 0; i < take; ++i) {
            addEdge(candidates[i].first, candidates[i].second, rnd.next(1, 100000));
        }
    }

    if (v > 1 && rnd.next(0, 3) == 0) {
        int a = rnd.next(1, v);
        int b = rnd.next(1, v);
        addEdge(a, b, rnd.next(1, 100));
    }
    if (!edges.empty() && rnd.next(0, 2) == 0) {
        auto edge = rnd.any(edges);
        addEdge(edge.first.first, edge.first.second, rnd.next(1, 100000));
    }

    vector<int> route;
    route.reserve(10);
    if (mode == 1 && v >= 10) {
        for (int i = 1; i <= 10; ++i) {
            route.push_back(i);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, v);
        for (int i = 0; i < 10; ++i) {
            if (i % 2 == 0) {
                route.push_back(rnd.next(1, split));
            } else {
                route.push_back(rnd.next(split, v));
            }
        }
    } else {
        int smallPool = rnd.next(1, min(v, 5));
        for (int i = 0; i < 10; ++i) {
            route.push_back(rnd.next(1, rnd.next(0, 2) == 0 ? smallPool : v));
        }
    }

    int start;
    if (rnd.next(0, 3) == 0) {
        start = rnd.any(route);
    } else {
        start = rnd.next(1, v);
    }

    println(v, static_cast<int>(edges.size()));
    for (auto edge : edges) {
        println(edge.first.first, edge.first.second, edge.second);
    }
    println(route);
    println(start);

    return 0;
}
