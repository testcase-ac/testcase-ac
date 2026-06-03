#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        long long value = inf.readLong(-2147483647LL, 2147483647LL, "a_i");
        ensuref(seen.insert(value).second,
                "duplicate array value at index %d: %lld", i + 1, value);
    }
    inf.readEoln();
    inf.readEof();
}
