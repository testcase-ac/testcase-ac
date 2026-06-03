#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200, "N");
    inf.readSpace();
    int m = inf.readInt(1, n * (n - 1), "M");
    inf.readEoln();

    const int INF = 1'000'000'000;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    set<pair<int, int>> roads;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000, "T_i");
        inf.readEoln();

        // CHECK: M's upper bound is N * (N - 1), so roads are between distinct ordered city pairs.
        ensuref(a != b, "road %d is a self-loop: %d -> %d", i, a, b);
        ensuref(roads.insert({a, b}).second, "duplicate directed road at index %d: %d -> %d", i, a, b);
        dist[a][b] = min(dist[a][b], t);
    }

    int k = inf.readInt(2, n, "K");
    inf.readEoln();
    vector<int> cities = inf.readInts(k, 1, n, "C_i");
    inf.readEoln();

    set<int> uniqueCities(cities.begin(), cities.end());
    ensuref(static_cast<int>(uniqueCities.size()) == k, "resident cities must be distinct");

    for (int mid = 1; mid <= n; ++mid) {
        for (int from = 1; from <= n; ++from) {
            for (int to = 1; to <= n; ++to) {
                if (dist[from][mid] < INF && dist[mid][to] < INF) {
                    dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
                }
            }
        }
    }

    bool hasMeetingCity = false;
    for (int x = 1; x <= n; ++x) {
        bool reachable = true;
        for (int city : cities) {
            if (dist[city][x] == INF || dist[x][city] == INF) {
                reachable = false;
                break;
            }
        }
        if (reachable) {
            hasMeetingCity = true;
            break;
        }
    }
    ensuref(hasMeetingCity, "no city has round-trip routes for every resident city");

    inf.readEof();
}
