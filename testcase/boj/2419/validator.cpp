#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(0, 300, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000LL, "m");
    inf.readEoln();

    // Read positions and check uniqueness
    set<int> xs;
    for (int i = 0; i < n; i++) {
        int xi = inf.readInt(-10000, 10000, "x_i");
        inf.readEoln();
        bool inserted = xs.insert(xi).second;
        ensuref(inserted, "Duplicate position at index %d: %d", i, xi);
    }

    inf.readEof();
    return 0;
}
