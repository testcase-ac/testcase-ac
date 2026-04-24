#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int h = inf.readInt(1, 700, "h");
    inf.readSpace();
    int w = inf.readInt(1, 700, "w");
    inf.readEoln();

    // Read and validate each row
    for (int i = 0; i < h; i++) {
        // Read a token consisting of O and X only
        string row = inf.readToken("[OX]+", "row");
        // Check exact length
        ensuref((int)row.size() == w,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), w);
        // No need to re-check characters; the regex enforces O/X only
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
