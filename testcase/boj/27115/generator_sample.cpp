#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

struct Station {
    int y;
    int x;
    int p;
};

int choosePower(int n, int m, int mode) {
    int localMax = max(1, min(3000, n + m));
    if (mode == 0) return rnd.next(1, min(5, localMax));
    if (mode == 1) return rnd.any(vector<int>{1, min(2, localMax), min(3000, max(n, m)), 3000});
    if (mode == 2) return rnd.next(max(1, localMax / 3), min(3000, localMax));
    return rnd.next(1, 3000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int m;
    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        m = rnd.next(2, 25);
    } else if (mode == 2) {
        n = rnd.next(8, 35);
        m = rnd.next(8, 35);
    } else {
        n = rnd.next(1, 3000);
        m = rnd.next(1, 3000);
    }

    int maxK = min(n * m, mode == 3 ? 45 : 90);
    int k;
    if (mode == 0) {
        k = rnd.next(1, maxK);
    } else {
        k = rnd.next(1, maxK);
        if (rnd.next(100) < 35) k = maxK;
    }

    int centerY = rnd.next(1, n);
    int centerX = rnd.next(1, m);
    vector<pair<int, int>> preferred;
    vector<pair<int, int>> fallback;
    int clusterRadius = max(1, min(n, m) / 3);
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) {
            bool isPreferred = false;
            if (mode == 1) {
                isPreferred = y == 1 || y == n || x == 1 || x == m;
            } else if (mode == 2) {
                isPreferred = abs(y - centerY) + abs(x - centerX) <= clusterRadius;
            }

            if (isPreferred) {
                preferred.push_back({y, x});
            } else {
                fallback.push_back({y, x});
            }
        }
    }
    shuffle(preferred.begin(), preferred.end());
    shuffle(fallback.begin(), fallback.end());

    vector<pair<int, int>> positions;
    for (auto position : preferred) {
        if ((int)positions.size() == k) break;
        positions.push_back(position);
    }
    for (auto position : fallback) {
        if ((int)positions.size() == k) break;
        positions.push_back(position);
    }
    if (mode == 0 || mode == 3) {
        shuffle(positions.begin(), positions.end());
    }

    vector<Station> stations;

    for (auto [y, x] : positions) {
        stations.push_back({y, x, choosePower(n, m, mode)});
    }

    shuffle(stations.begin(), stations.end());

    println(n, m, k);
    for (const Station& station : stations) {
        println(station.y, station.x, station.p);
    }

    return 0;
}
