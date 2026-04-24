#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(8, 50, "N");
    inf.readSpace();
    int M = inf.readInt(8, 50, "M");
    inf.readEoln();

    // Read the board rows
    for (int i = 0; i < N; i++) {
        // Read exactly one line of characters (no leading/trailing spaces)
        string row = inf.readLine("[BW]+", "row");
        // Check length
        ensuref((int)row.size() == M,
                "Row %d has length %d, but expected %d", i+1, (int)row.size(), M);
        // All characters are guaranteed B or W by the regex
    }

    inf.readEof();
    return 0;
}
