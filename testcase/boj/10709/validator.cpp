#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and W
    int H = inf.readInt(1, 100, "H");
    inf.readSpace();
    int W = inf.readInt(1, 100, "W");
    inf.readEoln();

    // Read H rows of the grid
    for (int i = 1; i <= H; i++) {
        // Each row must consist of exactly W characters, each 'c' or '.'
        string row = inf.readLine("[c\\.]{1,100}", "row");
        ensuref((int)row.size() == W,
                "Row %d length mismatch: expected %d, found %d",
                i, W, (int)row.size());
        // Characters are already guaranteed to be 'c' or '.' by the regex
    }

    inf.readEof();
    return 0;
}
