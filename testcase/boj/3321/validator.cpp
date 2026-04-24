#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 15000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1500, "M");
    inf.readEoln();

    // Read N lines of the matrix
    for (int i = 0; i < N; i++) {
        // Each row is a token of 0/1 of length exactly M
        string row = inf.readToken("[01]+", "row");
        // Check exact length
        ensuref((int)row.size() == M,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), M);
        // No further char checks needed: regex "[01]+" guarantees only '0' or '1'
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
