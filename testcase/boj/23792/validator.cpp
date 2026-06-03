#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_N = 100000;
constexpr int MAX_Q = 100000;
constexpr int MAX_TASTE = 2147483647;

void readTasteArray(int n, const char* name, set<int>& seen) {
    vector<int> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        int value = inf.readInt(1, MAX_TASTE, name);
        if (!values.empty()) {
            ensuref(values.back() < value,
                    "%s must be strictly increasing at index %d: %d then %d",
                    name,
                    i + 1,
                    values.back(),
                    value);
        }
        ensuref(seen.insert(value).second,
                "taste value must be globally distinct: %d",
                value);
        values.push_back(value);
    }

    inf.readEoln();
}
}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();

    set<int> seen;
    readTasteArray(n, "a_i", seen);
    readTasteArray(n, "b_i", seen);
    readTasteArray(n, "c_i", seen);

    int q = inf.readInt(1, MAX_Q, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        int z = inf.readInt(1, n, "z");
        inf.readSpace();
        int k = inf.readInt(1, 3 * n, "k");
        inf.readEoln();

        ensuref(k <= x + y + z,
                "query %d has k=%d greater than x+y+z=%d",
                i + 1,
                k,
                x + y + z);
    }

    inf.readEof();
}
