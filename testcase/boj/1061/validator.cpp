#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read the grid
    for (int i = 0; i < N; i++) {
        // Read a token of consecutive R/G/B characters
        string row = inf.readToken("[RGB]+", "row");
        // It must be exactly length M
        ensuref((int)row.size() == M,
                "Row %d has incorrect length %d, expected %d", 
                i+1, (int)row.size(), M);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
