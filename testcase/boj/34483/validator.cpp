#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
    inf.readSpace();
    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    set<int> pset;
    for (int i = 0; i < n; ++i) {
        int p = inf.readInt(1, 1000, "p_i");
        inf.readEoln();
        ensuref(pset.count(p) == 0, "Duplicate p_i value at index %d: %d", i+1, p);
        pset.insert(p);
    }

    inf.readEof();
}
