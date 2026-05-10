#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of floors F
    int F = inf.readInt(1, 1000000, "F");
    inf.readSpace();
    // Read starting floor S
    int S = inf.readInt(1, F, "S");
    inf.readSpace();
    // Read goal floor G
    int G = inf.readInt(1, F, "G");
    inf.readSpace();
    // Read up move U
    int U = inf.readInt(0, 1000000, "U");
    inf.readSpace();
    // Read down move D
    int D = inf.readInt(0, 1000000, "D");

    // End of line for the single test case
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
