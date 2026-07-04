#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct TestCase {
    int n;
    vector<int> stations;
    vector<int> waits;
    vector<vector<int>> times;
    vector<tuple<int, int, int, int, int>> tunnels;
    vector<tuple<int, int, int, int>> queries;
};

static pair<int, int> randomStation(const vector<int>& stations) {
    int line = rnd.next(1, static_cast<int>(stations.size()));
    return {line, rnd.next(1, stations[line - 1])};
}

static pair<int, int> randomDifferentStation(const vector<int>& stations,
                                             pair<int, int> source) {
    pair<int, int> target = source;
    while (target == source) {
        target = randomStation(stations);
    }
    return target;
}

static TestCase makeCase(int mode) {
    TestCase tc;

    if (mode == 0) {
        tc.n = 1;
    } else if (mode == 1) {
        tc.n = rnd.next(2, 4);
    } else if (mode == 2) {
        tc.n = rnd.next(3, 6);
    } else {
        tc.n = rnd.next(5, 10);
    }

    int remainingStations = 100;
    for (int i = 0; i < tc.n; ++i) {
        int remainingLines = tc.n - i - 1;
        int maxHere = min(remainingStations - 2 * remainingLines,
                          mode == 3 ? 16 : 8);
        int count = rnd.next(2, maxHere);
        tc.stations.push_back(count);
        remainingStations -= count;

        int wait = rnd.next(1, mode == 3 ? 100 : 15);
        tc.waits.push_back(wait);

        vector<int> lineTimes;
        for (int j = 0; j + 1 < count; ++j) {
            int travel = rnd.next(1, mode == 3 ? 100 : 20);
            if (mode == 2 && rnd.next(0, 3) == 0) {
                travel = 1;
            }
            lineTimes.push_back(travel);
        }
        tc.times.push_back(lineTimes);
    }

    vector<pair<int, int>> linePairs;
    for (int i = 1; i <= tc.n; ++i) {
        for (int j = i + 1; j <= tc.n; ++j) {
            linePairs.push_back({i, j});
        }
    }
    shuffle(linePairs.begin(), linePairs.end());

    int maxTunnels = min(10, static_cast<int>(linePairs.size()));
    int tunnelCount = 0;
    if (tc.n > 1) {
        if (mode == 1) {
            tunnelCount = rnd.next(0, maxTunnels);
        } else if (mode == 2) {
            tunnelCount = min(maxTunnels, rnd.next(tc.n - 1, tc.n + 2));
        } else if (mode == 3) {
            tunnelCount = rnd.next(max(1, maxTunnels / 2), maxTunnels);
        }
    }

    for (int i = 0; i < tunnelCount; ++i) {
        int a = linePairs[i].first;
        int b = linePairs[i].second;
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        int sa = rnd.next(1, tc.stations[a - 1]);
        int sb = rnd.next(1, tc.stations[b - 1]);
        int walk = rnd.next(1, mode == 3 ? 100 : 20);
        tc.tunnels.emplace_back(a, sa, b, sb, walk);
    }

    int queryCount = rnd.next(1, 10);
    for (int i = 0; i < queryCount; ++i) {
        pair<int, int> source = randomStation(tc.stations);
        pair<int, int> target = randomDifferentStation(tc.stations, source);

        if (mode == 0 || (mode == 1 && rnd.next(0, 2) == 0)) {
            target.first = source.first;
            target.second = rnd.next(1, tc.stations[source.first - 1]);
            if (target.second == source.second) {
                target.second = target.second % tc.stations[source.first - 1] + 1;
            }
        }

        tc.queries.emplace_back(source.first, source.second, target.first,
                                target.second);
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(2, 6);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        TestCase data = makeCase((tc + rnd.next(0, 3)) % 4);

        println(data.n);
        for (int i = 0; i < data.n; ++i) {
            println(data.stations[i], data.waits[i]);
            println(data.times[i]);
        }

        println(static_cast<int>(data.tunnels.size()));
        for (const auto& tunnel : data.tunnels) {
            int m1, s1, m2, s2, t;
            tie(m1, s1, m2, s2, t) = tunnel;
            println(m1, s1, m2, s2, t);
        }

        println(static_cast<int>(data.queries.size()));
        for (const auto& query : data.queries) {
            int x1, y1, x2, y2;
            tie(x1, y1, x2, y2) = query;
            println(x1, y1, x2, y2);
        }
    }

    return 0;
}
