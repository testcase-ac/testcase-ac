#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, 1000000000, "A_i");
        ensuref(seen.insert(value).second,
                "A_i values must be distinct, duplicate %d at position %d",
                value,
                i);
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
