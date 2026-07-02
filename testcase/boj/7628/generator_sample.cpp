#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000LL;

    vector<long long> powers;
    for (long long p = 1; p <= maxN; p *= 3) {
        powers.push_back(p);
        if (p > maxN / 3) {
            break;
        }
    }

    int queryCount = rnd.next(8, 24);
    vector<long long> queries;

    auto addQuery = [&](long long n) {
        n = max(1LL, min(maxN, n));
        queries.push_back(n);
    };

    int mode = rnd.next(5);
    if (mode == 0) {
        for (int i = 0; i < queryCount; ++i) {
            addQuery(rnd.next(1LL, 200LL));
        }
    } else if (mode == 1) {
        for (int i = 0; i < queryCount; ++i) {
            long long p = rnd.any(powers);
            addQuery(p + rnd.next(-3LL, 3LL));
        }
    } else if (mode == 2) {
        for (int i = 0; i < queryCount; ++i) {
            long long p = rnd.any(powers);
            long long offset = rnd.next(0LL, min(p - 1, 2000LL));
            addQuery(p + offset);
        }
    } else if (mode == 3) {
        for (int i = 0; i < queryCount; ++i) {
            addQuery(rnd.next(1LL, maxN));
        }
    } else {
        for (int i = 0; i < queryCount; ++i) {
            addQuery(maxN - rnd.next(0LL, 1000000LL));
        }
    }

    addQuery(1);
    addQuery(2);
    addQuery(3);
    addQuery(maxN);
    shuffle(queries.begin(), queries.end());

    for (long long n : queries) {
        println(n);
    }
    println(0);

    return 0;
}
