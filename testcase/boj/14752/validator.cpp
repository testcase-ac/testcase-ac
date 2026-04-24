#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Read coordinates a_i
    set<int> seen;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int ai = inf.readInt(0, 100000000, "a_i");
        ensuref(!seen.count(ai),
                "Duplicate coordinate detected at index %d: %d", i, ai);
        seen.insert(ai);
        a[i] = ai;
        inf.readEoln();
    }

    // Read widths w_i
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        w[i] = inf.readInt(1, 100000, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
