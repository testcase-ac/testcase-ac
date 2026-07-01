#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int c) {
    if (a > b) {
        swap(a, b);
    }
    if (used.emplace(a, b).second) {
        edges.push_back({a, b, c});
    }
}

int randCoord() {
    return rnd.next(-20, 20);
}

int randCost() {
    return rnd.next(0, 40);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    vector<pair<int, int>> points(n + 1);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            points[i] = {randCoord(), randCoord()};
        }
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (a == 1 || b == 1 || (a != 2 && b != 2)) {
                    candidates.push_back({a, b});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = rnd.next(0, min(8, (int)candidates.size()));
        for (int i = 0; i < extra; ++i) {
            addEdge(edges, used, candidates[i].first, candidates[i].second, randCost());
        }
    } else if (mode == 1) {
        n = rnd.next(4, 10);
        points.assign(n + 1, {0, 0});
        points[1] = {0, 0};
        points[2] = {10, 0};
        points[3] = {0, 10};
        points[4] = {10, 10};
        for (int i = 5; i <= n; ++i) {
            points[i] = {randCoord(), randCoord()};
        }
        addEdge(edges, used, 1, 2, rnd.next(20, 40));
        addEdge(edges, used, 1, 3, rnd.next(1, 10));
        addEdge(edges, used, 3, 4, rnd.next(1, 10));
        addEdge(edges, used, 2, 4, rnd.next(1, 10));
        addEdge(edges, used, 1, 4, rnd.next(1, 15));
        for (int i = 5; i <= n; ++i) {
            addEdge(edges, used, rnd.next(1, i - 1), i, randCost());
        }
    } else if (mode == 2) {
        n = rnd.next(5, 9);
        points.assign(n + 1, {0, 0});
        points[1] = {0, 0};
        points[2] = {10, 0};
        points[3] = {5, 0};
        points[4] = {5, 6};
        points[5] = {8, 3};
        for (int i = 6; i <= n; ++i) {
            points[i] = {rnd.next(-5, 15), rnd.next(-6, 12)};
        }
        addEdge(edges, used, 1, 3, rnd.next(1, 5));
        addEdge(edges, used, 2, 3, rnd.next(1, 5));
        addEdge(edges, used, 1, 4, rnd.next(1, 8));
        addEdge(edges, used, 2, 4, rnd.next(1, 8));
        addEdge(edges, used, 3, 5, rnd.next(1, 8));
        addEdge(edges, used, 2, 5, rnd.next(1, 8));
        for (int i = 6; i <= n; ++i) {
            addEdge(edges, used, rnd.next(1, i - 1), i, randCost());
            if (rnd.next(0, 1)) {
                addEdge(edges, used, rnd.next(1, i - 1), i, randCost());
            }
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            points[i] = {randCoord(), randCoord()};
        }
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        double density = rnd.next(0.15, mode == 3 ? 0.45 : 0.85);
        for (auto [a, b] : candidates) {
            if (rnd.next() < density) {
                addEdge(edges, used, a, b, randCost());
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (int i = 1; i <= n; ++i) {
        println(points[i].first, points[i].second);
    }
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c);
    }

    return 0;
}
