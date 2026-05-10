#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 500000;
    const long long MIN_COORD = -1000000000LL;
    const long long MAX_COORD =  1000000000LL;
    const long long MAX_L = 1000000000LL;
    const long long MAX_C = 1000000000LL;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    long long L = inf.readLong(1LL, MAX_L, "L");
    inf.readEoln();

    // Use a set to ensure all pirates have distinct integer coordinates
    // as guaranteed in the statement.
    struct PairHash {
        size_t operator()(const pair<long long,long long>& p) const {
            return std::hash<long long>()((p.first << 1) ^ (p.second + 0x9e3779b97f4a7c15ULL));
        }
    };
    unordered_set<pair<long long,long long>, PairHash> seen;
    seen.reserve(N * 2);

    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(MIN_COORD, MAX_COORD, "x_i");
        inf.readSpace();
        long long y = inf.readLong(MIN_COORD, MAX_COORD, "y_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, MAX_C, "c_i");
        inf.readEoln();

        ensuref(!(x == 0 && y == 0),
                "Pirate %d is at forbidden origin (0,0)", i + 1);

        pair<long long,long long> p = {x, y};
        ensuref(seen.find(p) == seen.end(),
                "Duplicate pirate position (%lld,%lld) at index %d",
                x, y, i + 1);
        seen.insert(p);
    }

    inf.readEof();
}
