#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int x;
    int y;
    int t;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int x, int y, int t) {
    if (x == y) {
        return;
    }
    if (x > y) {
        swap(x, y);
    }
    if (used.insert({x, y}).second) {
        edges.push_back({x, y, t});
    }
}

static int travelTime(int m, int mode) {
    if (mode == 0) {
        return rnd.next(0, max(0, m + 2));
    }
    if (mode == 1) {
        return rnd.next(0, m);
    }
    if (mode == 2) {
        return rnd.next(max(0, m - 1), m + 3);
    }
    return rnd.any(vector<int>{0, 1, m, min(1000000000, m + rnd.next(1, 7)), 1000000000});
}

static void printCase(int n, int m, int a, int h, vector<int> freezers, vector<Edge> edges) {
    shuffle(freezers.begin(), freezers.end());
    shuffle(edges.begin(), edges.end());

    println(n, m, int(freezers.size()), int(edges.size()), a, h);
    if (!freezers.empty()) {
        println(freezers);
    }
    for (const Edge& edge : edges) {
        if (rnd.next(0, 1) == 0) {
            println(edge.x, edge.y, edge.t);
        } else {
            println(edge.y, edge.x, edge.t);
        }
    }
}

static void makeSparseCase() {
    int n = rnd.next(2, 9);
    int m = rnd.next(1, 8);
    int a = rnd.next(0, n - 1);
    int h = rnd.next(0, n - 2);
    if (h >= a) {
        ++h;
    }

    vector<int> middle;
    for (int town = 0; town < n; ++town) {
        if (town != a && town != h) {
            middle.push_back(town);
        }
    }
    shuffle(middle.begin(), middle.end());
    int l = rnd.next(0, int(middle.size()));
    vector<int> freezers(middle.begin(), middle.begin() + l);

    vector<Edge> edges;
    set<pair<int, int>> used;
    for (int i = 1; i < n; ++i) {
        if (rnd.next(0, 3) != 0) {
            addEdge(edges, used, i - 1, i, travelTime(m, rnd.next(0, 3)));
        }
    }
    int extra = rnd.next(0, min(8, n * (n - 1) / 2 - int(edges.size())));
    while (extra--) {
        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 2);
        if (y >= x) {
            ++y;
        }
        addEdge(edges, used, x, y, travelTime(m, rnd.next(0, 3)));
    }

    printCase(n, m, a, h, freezers, edges);
}

static void makeRefreezePathCase() {
    int n = rnd.next(4, 10);
    int m = rnd.next(2, 12);
    vector<int> towns(n);
    iota(towns.begin(), towns.end(), 0);
    shuffle(towns.begin(), towns.end());

    int a = towns[0];
    int h = towns[1];
    int pathLen = rnd.next(3, min(n, 6));
    vector<int> path;
    path.push_back(a);
    for (int i = 2; int(path.size()) + 1 < pathLen; ++i) {
        path.push_back(towns[i]);
    }
    path.push_back(h);

    vector<int> freezers;
    for (int i = 1; i + 1 < pathLen; ++i) {
        if (rnd.next(0, 1) == 0) {
            freezers.push_back(path[i]);
        }
    }
    for (int town : towns) {
        if (town != a && town != h && find(path.begin(), path.end(), town) == path.end() && rnd.next(0, 3) == 0) {
            freezers.push_back(town);
        }
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    for (int i = 1; i < pathLen; ++i) {
        int base = rnd.next(max(1, m / 2), m);
        addEdge(edges, used, path[i - 1], path[i], base);
    }
    int extra = rnd.next(1, 7);
    while (extra--) {
        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 2);
        if (y >= x) {
            ++y;
        }
        addEdge(edges, used, x, y, travelTime(m, rnd.next(0, 3)));
    }

    printCase(n, m, a, h, freezers, edges);
}

static void makeDenseCase() {
    int n = rnd.next(5, 12);
    int m = rnd.next(1, 20);
    int a = rnd.next(0, n - 1);
    int h = rnd.next(0, n - 2);
    if (h >= a) {
        ++h;
    }

    vector<int> freezers;
    for (int town = 0; town < n; ++town) {
        if (town != a && town != h && rnd.next(0, 2) == 0) {
            freezers.push_back(town);
        }
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    double density = rnd.next(0.35, 0.8);
    for (int x = 0; x < n; ++x) {
        for (int y = x + 1; y < n; ++y) {
            if (rnd.next() < density) {
                addEdge(edges, used, x, y, travelTime(m, rnd.next(0, 3)));
            }
        }
    }
    if (edges.empty()) {
        addEdge(edges, used, a, h, travelTime(m, 1));
    }

    printCase(n, m, a, h, freezers, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 6);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            makeSparseCase();
        } else if (mode == 1) {
            makeRefreezePathCase();
        } else {
            makeDenseCase();
        }
    }
    println(0, 0, 0, 0, 0, 0);

    return 0;
}
