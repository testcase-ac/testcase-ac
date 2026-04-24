#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k and n
    int k = inf.readInt(1, 100000, "k");
    inf.readSpace();
    int n = inf.readInt(k, 1000000, "n");
    inf.readEoln();

    // Track that each type appears at least once
    vector<char> seen(k+1, 0);

    // Read n facility descriptions
    for (int i = 0; i < n; i++) {
        long long loc = inf.readLong(-1000000000LL, 1000000000LL, "location");
        inf.readSpace();
        int tp = inf.readInt(1, k, "type");
        inf.readEoln();

        // Mark type as seen
        seen[tp] = 1;
    }

    // Ensure every type from 1..k appears
    for (int t = 1; t <= k; t++) {
        ensuref(seen[t], "No facility of type %d present in input", t);
    }

    inf.readEof();
    return 0;
}
