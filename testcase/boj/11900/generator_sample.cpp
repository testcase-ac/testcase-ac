#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int positiveWeight(int scale) {
    if (scale == 0) return rnd.next(1, 9);
    if (scale == 1) return rnd.next(1, 100);
    return rnd.next(9000, 10000);
}

void addQuery(vector<pair<int, int>>& queries, int n, int from, int diff) {
    diff %= n;
    if (diff == 0) diff = 1;
    int to = (from + diff) % n;
    queries.push_back({from, to});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, mode == 5 ? 40 : 14);
    vector<int> a(n, 0);

    if (mode == 0) {
        // all zero weights
    } else if (mode == 1) {
        int step = rnd.next(1, n - 1);
        a[step] = positiveWeight(rnd.next(0, 2));
    } else if (mode == 2) {
        int step = rnd.next(2, n - 1);
        int weightScale = rnd.next(0, 1);
        for (int d = step; d < n; d += step) {
            a[d] = positiveWeight(weightScale);
        }
    } else if (mode == 3) {
        int weightScale = rnd.next(0, 1);
        for (int d = 1; d < n; ++d) {
            if (rnd.next(0, 99) < 45) {
                a[d] = positiveWeight(weightScale);
            }
        }
        if (count(a.begin() + 1, a.end(), 0) == n - 1) {
            a[rnd.next(1, n - 1)] = positiveWeight(weightScale);
        }
    } else if (mode == 4) {
        for (int d = 1; d < n; ++d) {
            a[d] = positiveWeight(rnd.next(0, 2));
        }
        int zeroCount = rnd.next(1, max(1, (n - 1) / 3));
        for (int i = 0; i < zeroCount; ++i) {
            a[rnd.next(1, n - 1)] = 0;
        }
    } else {
        int cheap = rnd.next(1, n - 1);
        int expensive = rnd.next(1, n - 1);
        while (expensive == cheap) expensive = rnd.next(1, n - 1);
        a[cheap] = rnd.next(1, 5);
        a[expensive] = rnd.next(7000, 10000);
        for (int d = 1; d < n; ++d) {
            if (d != cheap && d != expensive && rnd.next(0, 99) < 25) {
                a[d] = rnd.next(1, 30);
            }
        }
    }

    vector<pair<int, int>> queries;
    int queryTarget = rnd.next(8, 24);
    for (int d = 1; d < n && (int)queries.size() < queryTarget / 2; ++d) {
        if (a[d] > 0 || rnd.next(0, 99) < 35) {
            addQuery(queries, n, rnd.next(0, n - 1), d);
        }
    }
    while ((int)queries.size() < queryTarget) {
        int from = rnd.next(0, n - 1);
        int to = rnd.next(0, n - 2);
        if (to >= from) ++to;
        queries.push_back({from, to});
    }
    shuffle(queries.begin(), queries.end());

    println(n);
    vector<int> out(a.begin() + 1, a.end());
    println(out);
    println((int)queries.size());
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
