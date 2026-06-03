#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readEoln();

    vector<long long> beads = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(beads[i]).second,
                "duplicate bead value at index %d: %lld", i + 1, beads[i]);
    }

    inf.readEof();
    return 0;
}
