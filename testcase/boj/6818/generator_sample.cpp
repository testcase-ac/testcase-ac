#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Station {
    int x;
    int y;
    int r;
    int b;
};

static void addStation(vector<Station>& stations, set<pair<int, int>>& used, int n,
                       int m, int x, int y, int r, int b) {
    x = max(1, min(n, x));
    y = max(1, min(m, y));
    if (!used.insert({x, y}).second) return;
    stations.push_back({x, y, r, b});
}

static pair<int, int> unusedPoint(set<pair<int, int>>& used, int n, int m) {
    for (int tries = 0; tries < 1000; ++tries) {
        int x = rnd.next(1, n);
        int y = rnd.next(1, m);
        if (used.insert({x, y}).second) return {x, y};
    }

    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if (used.insert({x, y}).second) return {x, y};
        }
    }
    return {1, 1};
}

static vector<Station> makeRandomStations(int n, int m, int k, int maxRadius) {
    vector<Station> stations;
    set<pair<int, int>> used;
    for (int i = 0; i < k; ++i) {
        auto point = unusedPoint(used, n, m);
        int r = rnd.next(1, maxRadius);
        int b = rnd.next(1, 1000);
        stations.push_back({point.first, point.second, r, b});
    }
    return stations;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int m = rnd.next(2, 40);
    int n = rnd.next(2, 25);
    vector<Station> stations;
    set<pair<int, int>> used;

    if (mode == 0) {
        m = rnd.next(1, 8);
        n = rnd.next(1, 8);
        int k = rnd.next(1, min(8, n * m));
        stations = makeRandomStations(n, m, k, 6);
    } else if (mode == 1) {
        m = rnd.next(8, 35);
        n = rnd.next(8, 25);
        int centerX = rnd.next(2, n - 1);
        int centerY = rnd.next(2, m - 1);
        int k = rnd.next(4, 12);
        for (int i = 0; i < k; ++i) {
            int x = centerX + rnd.next(-3, 3);
            int y = centerY + rnd.next(-3, 3);
            int r = rnd.next(1, 12);
            int b = rnd.next(1, 40);
            addStation(stations, used, n, m, x, y, r, b);
        }
        while ((int)stations.size() < k) {
            auto point = unusedPoint(used, n, m);
            stations.push_back({point.first, point.second, rnd.next(1, 12),
                                rnd.next(1, 40)});
        }
    } else if (mode == 2) {
        m = rnd.any(vector<int>{1, 2, 999, 1000, 30000});
        n = rnd.any(vector<int>{1, 2, 999, 1000});
        vector<pair<int, int>> candidates = {
            {1, 1}, {n, 1}, {1, m}, {n, m}, {(n + 1) / 2, (m + 1) / 2},
        };
        shuffle(candidates.begin(), candidates.end());
        int k = rnd.next(1, min((int)candidates.size(), n * m));
        for (int i = 0; i < k; ++i) {
            int r = rnd.any(vector<int>{1, 2, 999, 1000, 30000});
            int b = rnd.any(vector<int>{1, 2, 999, 1000});
            addStation(stations, used, n, m, candidates[i].first,
                       candidates[i].second, r, b);
        }
    } else if (mode == 3) {
        m = rnd.next(20, 80);
        n = rnd.next(1, 6);
        int k = rnd.next(3, min(18, n * m));
        stations = makeRandomStations(n, m, k, 30);
        for (Station& station : stations) {
            station.r = rnd.next(1, 20);
            station.b = rnd.next(1, 100);
        }
    } else {
        m = rnd.next(15, 60);
        n = rnd.next(15, 60);
        int k = rnd.next(8, 25);
        stations = makeRandomStations(n, m, k, 30000);
        for (Station& station : stations) {
            if (rnd.next(0, 3) == 0) station.r = rnd.any(vector<int>{1, 2, 30000});
            if (rnd.next(0, 4) == 0) station.b = rnd.any(vector<int>{1, 1000});
        }
    }

    println(m);
    println(n);
    println((int)stations.size());
    for (const Station& station : stations) {
        println(station.x, station.y, station.r, station.b);
    }

    return 0;
}
