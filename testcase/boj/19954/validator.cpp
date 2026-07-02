#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000LL, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "M");
    inf.readSpace();
    int x = inf.readInt(1, 200000, "X");
    inf.readEoln();

    set<pair<long long, long long>> occupied;
    for (int i = 1; i <= x; ++i) {
        long long a = inf.readLong(2LL, n, "A_i");
        inf.readSpace();
        long long b = inf.readLong(1LL, m, "B_i");
        inf.readSpace();
        int c = inf.readInt(-1, 1, "C_i");
        inf.readEoln();

        ensuref(c == -1 || c == 1, "C_%d must be -1 or 1, found %d", i, c);
        ensuref(occupied.insert({a, b}).second,
                "duplicate starting cell at banana %d: (%lld, %lld)", i, a, b);
    }

    inf.readEof();
}
