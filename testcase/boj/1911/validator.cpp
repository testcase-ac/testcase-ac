#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    // Read the puddles
    vector<pair<long long, long long>> puddles;
    puddles.reserve(N);
    for (int i = 0; i < N; i++) {
        long long l = inf.readLong(0LL, 1000000000LL, "l_i");
        inf.readSpace();
        long long r = inf.readLong(0LL, 1000000000LL, "r_i");
        inf.readEoln();
        puddles.emplace_back(l, r);
    }

    // Sort by start position
    sort(puddles.begin(), puddles.end());

    // Validate non-degeneracy and non-overlap
    for (int i = 0; i < N; i++) {
        long long l = puddles[i].first;
        long long r = puddles[i].second;
        ensuref(l < r,
                "Puddle %d is degenerate or inverted: start = %lld, end = %lld", 
                i, l, r);
        if (i > 0) {
            long long pl = puddles[i-1].first;
            long long pr = puddles[i-1].second;
            ensuref(pr <= l,
                    "Puddles %d and %d overlap or touch improperly: [%lld, %lld] vs [%lld, %lld]",
                    i-1, i, pl, pr, l, r);
        }
    }

    inf.readEof();
    return 0;
}
