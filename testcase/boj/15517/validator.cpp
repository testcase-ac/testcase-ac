#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        long long value = inf.readLong(-2000000000LL, 2000000000LL, "A_i");
        inf.readEoln();
        ensuref(seen.insert(value).second, "A[%d] is not distinct: %lld", i + 1, value);
    }

    inf.readEof();
}
