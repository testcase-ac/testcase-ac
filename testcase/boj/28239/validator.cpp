#include "testlib.h"

using namespace std;

static bool hasUniqueRepresentation(long long m) {
    return m >= 2 && __builtin_popcountll(static_cast<unsigned long long>(m)) <= 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
        inf.readEoln();
        ensuref(hasUniqueRepresentation(m),
                "m at index %d must have exactly one representation as 2^x + 2^y with x <= y: %lld",
                i + 1,
                m);
    }

    inf.readEof();
}
