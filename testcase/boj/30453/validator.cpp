#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of stars
    int n = inf.readInt(1, 3000, "n");
    inf.readEoln();

    // Read the n distinct points
    set<pair<long long, long long>> pts;
    for (int i = 0; i < n; i++) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();
        // Ensure no two stars share the same coordinates
        ensuref(!pts.count({x, y}),
                "Duplicate point at index %d: (%lld, %lld)", 
                i + 1, x, y);
        pts.insert({x, y});
    }

    inf.readEof();
    return 0;
}
