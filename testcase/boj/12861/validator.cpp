#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 10000, "P");
    inf.readSpace();
    int q = inf.readInt(1, 100, "Q");
    inf.readEoln();

    ensuref(q <= p, "Q must not exceed P: Q=%d, P=%d", q, p);

    vector<int> a = inf.readInts(q, 1, p, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < q; ++i) {
        ensuref(seen.insert(a[i]).second,
                "duplicate room number at index %d: %d", i + 1, a[i]);
    }

    inf.readEof();
}
