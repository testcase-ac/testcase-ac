#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    int m = inf.readInt(0, 250000, "m");
    inf.readEoln();

    set<pair<int, int>> redSegments;
    for (int i = 0; i < m; ++i) {
        int p = inf.readInt(1, n, "p");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");
        inf.readEoln();

        ensuref(p < k, "red segment %d has p >= k: %d %d", i + 1, p, k);
        // CHECK: A list of red segments is interpreted as a set, so duplicates are invalid.
        ensuref(redSegments.insert({p, k}).second,
                "duplicate red segment at index %d: %d %d", i + 1, p, k);
    }

    inf.readEof();
}
