#include "testlib.h"

#include <cstdlib>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(3LL, 1000000000LL, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    long long king_r = inf.readLong(1LL, n, "R");
    inf.readSpace();
    long long king_c = inf.readLong(1LL, n, "C");
    inf.readEoln();

    set<pair<long long, long long>> occupied;
    occupied.insert({king_r, king_c});

    for (int i = 1; i <= k; ++i) {
        long long r = inf.readLong(1LL, n, "R_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, n, "C_i");
        inf.readEoln();

        ensuref(occupied.insert({r, c}).second,
                "piece positions must be distinct, duplicate at queen %d: (%lld, %lld)",
                i, r, c);
        ensuref(llabs(r - king_r) > 1 || llabs(c - king_c) > 1,
                "queen %d is adjacent to the king: king=(%lld, %lld), queen=(%lld, %lld)",
                i, king_r, king_c, r, c);
    }

    inf.readEof();
}
