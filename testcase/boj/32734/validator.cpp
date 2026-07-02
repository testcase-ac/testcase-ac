#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        long long ai = inf.readLong(1LL, 1000000000000000000LL, "a_i");
        ensuref(seen.insert(ai).second, "a_i values must be distinct, duplicate at index %d: %lld", i + 1, ai);

        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
