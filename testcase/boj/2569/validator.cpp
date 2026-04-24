#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of containers
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read weights, one per line
    set<int> seen;
    for (int i = 0; i < n; i++) {
        int w = inf.readInt(1, 10000, "w_i");
        inf.readEoln();
        // Check for distinctness
        ensuref(!seen.count(w),
                "Duplicate weight at index %d: %d",
                i + 1, w);
        seen.insert(w);
    }

    // No extra tokens
    inf.readEof();
    return 0;
}
