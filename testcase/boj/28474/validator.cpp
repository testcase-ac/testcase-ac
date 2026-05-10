#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    set<int> seen_n;
    for (int tc = 0; tc < T; ++tc) {
        int n = inf.readInt(1, 1000000000, "n");
        inf.readEoln();

        // No further constraints on n (e.g., distinctness), but let's check for duplicates if needed
        // (Not required by statement, so we skip this)
    }

    inf.readEof();
}
