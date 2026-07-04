#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> stations;
    vector<int> waits;
    vector<vector<int>> travel;
    vector<vector<int>> station_ids;
    vector<tuple<int, int, int, int, int>> tunnels;
    vector<tuple<int, int, int, int>> queries;
};

pair<int, int> randomStation(const TestCase& tc) {
    int line = rnd.next(1, tc.n);
    int station = rnd.next(1, tc.stations[line]);
    return {line, station};
}

pair<int, int> randomDifferentStation(const TestCase& tc, pair<int, int> first) {
    pair<int, int> second = randomStation(tc);
    while (second == first) {
        second = randomStation(tc);
    }
    return second;
}

TestCase buildCase(int mode) {
    TestCase tc;

    if (mode == 0) {
        tc.n = 1;
    } else if (mode == 1) {
        tc.n = rnd.next(2, 4);
    } else if (mode == 2) {
        tc.n = rnd.next(3, 6);
    } else {
        tc.n = rnd.next(2, 8);
    }

    tc.stations.assign(tc.n + 1, 0);
    tc.waits.assign(tc.n + 1, 0);
    tc.travel.assign(tc.n + 1, {});
    tc.station_ids.assign(tc.n + 1, {});

    int total = 0;
    for (int i = 1; i <= tc.n; ++i) {
        int sn = 2;
        if (mode == 0) {
            sn = rnd.next(2, 12);
        } else if (mode == 1) {
            sn = rnd.next(2, 6);
        } else if (mode == 2) {
            sn = rnd.next(2, 8);
        } else {
            sn = rnd.next(2, 10);
        }

        tc.stations[i] = sn;
        tc.waits[i] = rnd.next(1, 20);
        total += sn;

        tc.station_ids[i].resize(sn + 1);
        for (int s = 1; s <= sn; ++s) {
            tc.station_ids[i][s] = total - sn + s;
        }

        tc.travel[i].resize(sn - 1);
        for (int s = 0; s < sn - 1; ++s) {
            if (mode == 1 && rnd.next(0, 3) == 0) {
                tc.travel[i][s] = rnd.next(50, 100);
            } else {
                tc.travel[i][s] = rnd.next(1, 25);
            }
        }
    }

    vector<pair<int, int>> line_pairs;
    for (int i = 1; i <= tc.n; ++i) {
        for (int j = i + 1; j <= tc.n; ++j) {
            line_pairs.push_back({i, j});
        }
    }
    shuffle(line_pairs.begin(), line_pairs.end());

    int tunnel_target = 0;
    if (mode == 1) {
        tunnel_target = rnd.next(0, min<int>(2, line_pairs.size()));
    } else if (mode == 2) {
        tunnel_target = min<int>(tc.n - 1, line_pairs.size());
    } else if (mode == 3) {
        tunnel_target = rnd.next(min<int>(tc.n - 1, line_pairs.size()),
                                 min<int>(100, line_pairs.size() * 2));
    }

    for (int i = 0; i < tunnel_target && i < static_cast<int>(line_pairs.size()); ++i) {
        int a = line_pairs[i].first;
        int b = line_pairs[i].second;
        int sa = rnd.next(1, tc.stations[a]);
        int sb = rnd.next(1, tc.stations[b]);
        int cost = (mode == 3 && rnd.next(0, 2) == 0) ? rnd.next(1, 5) : rnd.next(1, 40);
        tc.tunnels.emplace_back(a, sa, b, sb, cost);
    }

    while (static_cast<int>(tc.tunnels.size()) < tunnel_target) {
        int a = rnd.next(1, tc.n);
        int b = rnd.next(1, tc.n);
        if (a == b) {
            continue;
        }
        int sa = rnd.next(1, tc.stations[a]);
        int sb = rnd.next(1, tc.stations[b]);
        int cost = rnd.next(1, 30);
        tc.tunnels.emplace_back(a, sa, b, sb, cost);
    }

    int q = rnd.next(1, 10);
    for (int i = 0; i < q; ++i) {
        pair<int, int> from;
        pair<int, int> to;
        if (mode == 0 || rnd.next(0, 2) == 0) {
            int line = rnd.next(1, tc.n);
            from = {line, rnd.next(1, tc.stations[line])};
            to = {line, rnd.next(1, tc.stations[line])};
            while (to == from) {
                to.second = rnd.next(1, tc.stations[line]);
            }
        } else {
            from = randomStation(tc);
            to = randomDifferentStation(tc, from);
        }
        tc.queries.emplace_back(from.first, from.second, to.first, to.second);
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int case_id = 0; case_id < t; ++case_id) {
        TestCase tc = buildCase(rnd.next(0, 3));

        println(tc.n);
        for (int i = 1; i <= tc.n; ++i) {
            println(tc.stations[i], tc.waits[i]);
            println(tc.travel[i]);
        }

        println(static_cast<int>(tc.tunnels.size()));
        for (const auto& tunnel : tc.tunnels) {
            int m1, s1, m2, s2, cost;
            tie(m1, s1, m2, s2, cost) = tunnel;
            println(m1, s1, m2, s2, cost);
        }

        println(static_cast<int>(tc.queries.size()));
        for (const auto& query : tc.queries) {
            int x1, y1, x2, y2;
            tie(x1, y1, x2, y2) = query;
            println(x1, y1, x2, y2);
        }
    }

    return 0;
}
