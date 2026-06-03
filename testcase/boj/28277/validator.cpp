#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    long long totalElements = 0;
    for (int i = 1; i <= n; ++i) {
        int size = inf.readInt(0, 500000, "n_i");
        totalElements += size;
        ensuref(totalElements <= 500000, "sum of n_i exceeds 500000");

        unordered_set<int> seen;
        seen.reserve(size * 2 + 1);
        for (int j = 1; j <= size; ++j) {
            inf.readSpace();
            int value = inf.readInt(1, 1000000000, "s_ij");
            ensuref(seen.insert(value).second,
                    "duplicate element in S_%d at position %d: %d", i, j, value);
        }
        inf.readEoln();
    }
    ensuref(totalElements >= 1, "sum of n_i must be at least 1");

    bool hasSizeQuery = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "command_type");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        if (type == 1) {
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            ensuref(a != b, "merge command has equal indices at command %d: %d", i, a);
        } else {
            hasSizeQuery = true;
        }
        inf.readEoln();
    }
    ensuref(hasSizeQuery, "at least one type 2 command is required");

    inf.readEof();
}
