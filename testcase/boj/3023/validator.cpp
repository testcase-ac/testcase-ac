#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C
    int R = inf.readInt(1, 50, "R");
    inf.readSpace();
    int C = inf.readInt(1, 50, "C");
    inf.readEoln();

    // Read the R rows of the upper-left design
    for (int i = 0; i < R; i++) {
        // Each row must consist only of '.' or '#'
        string row = inf.readLine("[.#]+", "row");
        ensuref((int)row.size() == C,
                "Row %d length must be exactly %d but is %d",
                i+1, C, (int)row.size());
    }

    // Read error position A, B
    int A = inf.readInt(1, 2*R, "A");
    inf.readSpace();
    int B = inf.readInt(1, 2*C, "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
