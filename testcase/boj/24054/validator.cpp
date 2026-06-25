#include "testlib.h"

#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "A_i");
    inf.readEoln();

    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second,
                "duplicate A_i at position %d: %d", i + 1, a[i]);
    }

    inf.readEof();
    return 0;
}
