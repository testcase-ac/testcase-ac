#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int M = inf.readInt(0, 400, "M"); // M can be zero as per sample 2
    inf.readEoln();

    // Read the M prohibited pairs
    for (int i = 1; i <= M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();

        // No self‐loops allowed
        ensuref(a != b,
                "Pair %d has identical ingredients: %d and %d",
                i, a, b);
        // Duplicates are allowed per statement, so no check here
    }

    // No extra content after last line
    inf.readEof();
    return 0;
}
