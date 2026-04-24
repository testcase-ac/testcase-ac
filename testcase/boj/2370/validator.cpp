#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of posters
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // For each poster, read left and right endpoints
    for (int i = 0; i < n; i++) {
        int l = inf.readInt(1, 100000000, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, 100000000, "r_i");
        inf.readEoln();

        // Validate that l < r
        ensuref(l < r,
                "Poster %d has invalid interval: l (%d) is not less than r (%d)",
                i+1, l, r);
    }

    // No extra data
    inf.readEof();
    return 0;
}
