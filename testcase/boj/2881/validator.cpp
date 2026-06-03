#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long kMaxCoord = 1000000000LL;

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    set<pair<long long, long long>> trees;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(1LL, kMaxCoord, "X");
        inf.readSpace();
        long long y = inf.readLong(1LL, kMaxCoord, "Y");
        inf.readEoln();

        ensuref(trees.insert({x, y}).second,
                "duplicate tree coordinate at index %d: (%lld, %lld)", i + 1, x, y);
    }

    int p = inf.readInt(1, 100000, "P");
    inf.readEoln();

    for (int i = 0; i < p; ++i) {
        long long x1 = inf.readLong(1LL, kMaxCoord, "X1");
        inf.readSpace();
        long long y1 = inf.readLong(1LL, kMaxCoord, "Y1");
        inf.readSpace();
        long long x2 = inf.readLong(1LL, kMaxCoord, "X2");
        inf.readSpace();
        long long y2 = inf.readLong(1LL, kMaxCoord, "Y2");
        inf.readEoln();

        ensuref(x1 < x2, "rectangle %d must satisfy X1 < X2, got %lld >= %lld",
                i + 1, x1, x2);
        ensuref(y1 < y2, "rectangle %d must satisfy Y1 < Y2, got %lld >= %lld",
                i + 1, y1, y2);
    }

    inf.readEof();
}
