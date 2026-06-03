#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    unordered_set<long long> weights;
    weights.reserve(static_cast<size_t>(m) * 2);
    bool has_query = false;

    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            int x = inf.readInt(1, 1000000, "x");
            inf.readSpace();
            long long w = inf.readLong(1LL, 1000000000LL, "w");
            inf.readEoln();

            ensuref(weights.insert(w).second,
                    "duplicate bowling ball weight at request %d: %lld", i, w);
        } else {
            long long w = inf.readLong(1LL, 1000000000LL, "w");
            inf.readEoln();

            ensuref(weights.count(w) != 0,
                    "query at request %d references absent weight: %lld", i, w);
            has_query = true;
        }
    }

    ensuref(has_query, "at least one type 2 request is required");
    inf.readEof();
}
