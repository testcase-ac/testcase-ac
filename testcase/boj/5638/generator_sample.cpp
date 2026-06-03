#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

long long clampVolume(long long value) {
    return max(1LL, min(1000000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    if (mode == 1) n = 1;
    if (mode == 2) n = rnd.next(16, 20);

    vector<pair<long long, long long>> gates;
    gates.reserve(n);

    if (mode == 1) {
        gates.push_back({rnd.next(1, 25), rnd.next(1, 25)});
    } else if (mode == 2) {
        long long baseFlow = rnd.next(900000000LL, 1000000000LL);
        long long baseCost = rnd.next(900000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            gates.push_back({max(1LL, baseFlow - rnd.next(0, 2000000)),
                             max(1LL, baseCost - rnd.next(0, 2000000))});
        }
    } else if (mode == 3) {
        long long cost = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            gates.push_back({rnd.next(1, 2000000), cost + rnd.next(0, 3)});
        }
    } else if (mode == 4) {
        long long flow = rnd.next(1, 5000000);
        for (int i = 0; i < n; ++i) {
            gates.push_back({flow + rnd.next(0LL, 10LL), rnd.next(1LL, 1000000000LL)});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long flow = rnd.next(1, 5000000);
            long long cost = rnd.next(1, 5000000);
            if (rnd.next(0, 9) == 0) flow = rnd.next(1LL, 1000000000LL);
            if (rnd.next(0, 9) == 0) cost = rnd.next(1LL, 1000000000LL);
            gates.push_back({flow, cost});
        }
    }

    shuffle(gates.begin(), gates.end());

    int m = rnd.next(4, 18);
    if (mode == 1) m = rnd.next(1, 8);

    vector<pair<long long, int>> queries;
    queries.reserve(m);

    long long totalFlow = 0;
    for (auto gate : gates) totalFlow += gate.first;

    for (int i = 0; i < m; ++i) {
        int t = rnd.next(1, 1000);
        long long volume;

        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            volume = rnd.next(1LL, 1000000000LL);
        } else if (queryMode == 1) {
            int take = rnd.next(1, n);
            shuffle(gates.begin(), gates.end());
            long long flow = 0;
            for (int j = 0; j < take; ++j) flow += gates[j].first;
            long long exact = flow * t;
            long long delta = rnd.next(-3LL, 3LL);
            volume = clampVolume(exact + delta);
        } else if (queryMode == 2) {
            volume = clampVolume(totalFlow * t + rnd.next(1, 1000));
        } else if (queryMode == 3) {
            t = rnd.any(vector<int>{1, 2, 999, 1000});
            volume = rnd.next(1LL, 1000000000LL);
        } else {
            volume = clampVolume(rnd.any(gates).first * t);
        }

        queries.push_back({volume, t});
    }

    println(n);
    for (auto gate : gates) println(gate.first, gate.second);
    println(m);
    for (auto query : queries) println(query.first, query.second);

    return 0;
}
