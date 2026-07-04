#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long digitsUpTo(long long n) {
    long long total = 0;
    long long start = 1;
    for (int len = 1; start <= n; ++len) {
        long long end = min(n, start * 10 - 1);
        total += (end - start + 1) * len;
        start *= 10;
    }
    return total;
}

int clampN(long long n) {
    return (int)max(1LL, min(1000000000LL, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> queries;

    int queryCount = rnd.next(6, 15);
    vector<long long> anchors = {
        1, 8, 9, 10, 11,
        digitsUpTo(9), digitsUpTo(10), digitsUpTo(99), digitsUpTo(100),
        digitsUpTo(999), digitsUpTo(1000), digitsUpTo(9999),
        1000000000LL - 150, 1000000000LL
    };

    for (int i = 0; i < queryCount; ++i) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 200);
        } else if (mode == 1) {
            long long base = rnd.any(anchors);
            n = clampN(base + rnd.next(-12, 12));
        } else if (mode == 2) {
            n = rnd.next(999999800, 1000000000);
        } else {
            int len = rnd.next(1, 9);
            long long first = 1;
            for (int j = 1; j < len; ++j) first *= 10;
            long long value = rnd.next(first, min(1000000000LL, first * 10 - 1));
            n = clampN(digitsUpTo(value) + rnd.next(-30, 30));
        }

        int k = rnd.next(1, 100);
        queries.push_back({n, k});
    }

    shuffle(queries.begin(), queries.end());
    for (auto query : queries) {
        println(query.first, query.second);
    }
    println(0, 0);

    return 0;
}
