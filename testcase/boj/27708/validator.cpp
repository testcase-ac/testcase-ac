#include "testlib.h"

#include <climits>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound T; cap it so N <= 1000 keeps inputs practical.
    int t = inf.readInt(1, 5000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readEoln();

        int n = inf.readInt(3, 1000, "N");
        inf.readEoln();

        vector<long long> values;
        values.reserve(n);
        set<long long> seen;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            long long value = inf.readLong(static_cast<long long>(INT_MIN),
                                           static_cast<long long>(INT_MAX),
                                           "S_i");
            ensuref(seen.insert(value).second,
                    "duplicate sequence value at index %d: %lld", i + 1, value);
            values.push_back(value);
        }
        inf.readEoln();
    }

    inf.readEof();
}
