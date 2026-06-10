#include "testlib.h"
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        long long value = inf.readLong(1LL, 1000000000000000000LL, "A_i");
        inf.readEoln();

        ensuref(seen.insert(value).second,
                "duplicate value at index %d: %lld", i + 1, value);
    }

    inf.readEof();
}
