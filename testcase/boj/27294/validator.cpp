#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read hour T: integer in [0, 23]
    int T = inf.readInt(0, 23, "T");
    inf.readSpace();
    // Read alcohol flag S: integer in [0, 1]
    int S = inf.readInt(0, 1, "S");
    inf.readEoln();

    // No additional global constraints to check.
    inf.readEof();
    return 0;
}
