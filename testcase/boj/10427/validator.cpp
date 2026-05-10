#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // 2. Read N
        int N = inf.readInt(1, 4000, "N");
        inf.readSpace();

        // 3. Read A[1..N]
        vector<int> A = inf.readInts(N, 1, 10000, "A_i");
        inf.readEoln();

        // No further global constraints to check.
        // (No requirement to check answer existence, etc.)
    }

    inf.readEof();
}
