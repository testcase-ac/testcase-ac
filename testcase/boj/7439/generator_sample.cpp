#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> randomUnusedPoint(set<pair<int, int>>& used, int spread) {
    while (true) {
        pair<int, int> point = {rnd.next(-spread, spread), rnd.next(-spread, spread)};
        if (used.insert(point).second) {
            return point;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    if (mode == 4) {
        n = rnd.next(20, 35);
    }

    int spread = rnd.next(4, 25);
    set<pair<int, int>> usedPoints;
    vector<pair<int, int>> points;
    points.reserve(n);

    if (mode == 1) {
        int y = rnd.next(-spread, spread);
        int start = rnd.next(-spread, spread);
        for (int i = 0; i < n; ++i) {
            pair<int, int> point = {start + i * rnd.next(1, 3), y};
            if (!usedPoints.insert(point).second) {
                point = randomUnusedPoint(usedPoints, spread * 2);
            }
            points.push_back(point);
        }
    } else if (mode == 2) {
        int side = max(2, rnd.next(2, 8));
        while ((int)points.size() < n) {
            int x = rnd.next(0, side - 1);
            int y = rnd.next(0, side - 1);
            pair<int, int> point = {x * rnd.next(1, 3), y * rnd.next(1, 3)};
            if (usedPoints.insert(point).second) {
                points.push_back(point);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int cluster = rnd.next(0, 2);
            int baseX = (cluster - 1) * rnd.next(8, 20);
            int baseY = cluster * rnd.next(-3, 3);
            pair<int, int> point = {baseX + rnd.next(-2, 2), baseY + rnd.next(-2, 2)};
            if (!usedPoints.insert(point).second) {
                point = randomUnusedPoint(usedPoints, spread);
            }
            points.push_back(point);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            points.push_back(randomUnusedPoint(usedPoints, spread));
        }
    }

    vector<pair<int, int>> candidateEdges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            candidateEdges.push_back({i, j});
        }
    }
    shuffle(candidateEdges.begin(), candidateEdges.end());

    vector<pair<int, int>> edges;
    if (n > 1) {
        if (mode == 0) {
            int maxEdges = min<int>(1000, candidateEdges.size());
            int m = rnd.next(0, min(maxEdges, n + 5));
            edges.assign(candidateEdges.begin(), candidateEdges.begin() + m);
        } else if (mode == 1) {
            for (int i = 1; i < n; ++i) {
                if (rnd.next(0, 2) != 0) {
                    edges.push_back({i, i + 1});
                }
            }
        } else if (mode == 2) {
            int components = rnd.next(1, min(n, 4));
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    if (i % components == j % components && rnd.next(0, 1)) {
                        edges.push_back({i, j});
                    }
                }
            }
        } else {
            int maxEdges = min<int>(1000, candidateEdges.size());
            int m = rnd.next(min(maxEdges, n - 1), min(maxEdges, n * 2));
            edges.assign(candidateEdges.begin(), candidateEdges.begin() + m);
        }
    }

    println(n);
    for (const auto& point : points) {
        println(point.first, point.second);
    }
    println((int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
