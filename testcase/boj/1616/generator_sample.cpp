#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

const long long LIMIT = 10000000;

long long powLimited(int k, int m) {
    long long value = 1;
    for (int i = 0; i < m; ++i) {
        if (value > LIMIT / k) return LIMIT + 1;
        value *= k;
    }
    return value;
}

vector<pair<int, int>> buildSmallCases() {
    vector<pair<int, int>> cases;
    for (int k = 2; k <= 20; ++k) {
        for (int m = 1; m <= 12; ++m) {
            long long combinations = powLimited(k, m);
            if (combinations <= LIMIT) cases.push_back({k, m});
        }
    }
    return cases;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = 2;
    int m = 1;

    if (mode == 0) {
        m = 1;
        k = rnd.next(2, 10000000);
    } else if (mode == 1) {
        k = 2;
        m = rnd.next(1, 23);
    } else if (mode == 2) {
        vector<pair<int, int>> cases = buildSmallCases();
        auto chosen = rnd.any(cases);
        k = chosen.first;
        m = chosen.second;
    } else if (mode == 3) {
        int targetM = rnd.next(2, 8);
        int maxK = 2;
        while (powLimited(maxK + 1, targetM) <= LIMIT) ++maxK;
        k = rnd.next(max(2, maxK - 3), maxK);
        m = targetM;
    } else if (mode == 4) {
        vector<pair<int, int>> edges = {
            {2, 23}, {3, 14}, {4, 11}, {5, 10}, {10, 7},
            {20, 5}, {100, 3}, {215, 3}, {1000, 2}, {3162, 2}
        };
        auto chosen = rnd.any(edges);
        k = chosen.first;
        m = chosen.second;
    } else {
        k = rnd.next(2, 1000);
        m = 1;
        while (m < 23 && powLimited(k, m + 1) <= LIMIT && rnd.next(0, 1)) ++m;
    }

    println(k, m);
    return 0;
}
