#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 40, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string pile = inf.readToken("[BW]{1,40}", "p_i");
        inf.readEoln();

        // Check that pile is not empty (already ensured by regex {1,40})
        // Check that only 'B' and 'W' are present (already ensured by regex)
        // No further per-pile constraints
    }

    inf.readEof();
}
