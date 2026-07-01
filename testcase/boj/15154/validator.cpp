#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    long long d = inf.readLong(2LL, 1000000000LL, "D");
    inf.readEoln();

    set<long long> positions;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(1LL, d - 1, "x");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "a");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "g");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "r");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "traffic light positions must be distinct, duplicate x=%lld",
                x);
    }

    inf.readEof();
}
