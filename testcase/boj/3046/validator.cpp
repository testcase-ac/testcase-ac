#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R1 and S, both must be integers in [-1000, 1000]
    int R1 = inf.readInt(-1000, 1000, "R1");
    inf.readSpace();  // exactly one space between R1 and S
    int S  = inf.readInt(-1000, 1000, "S");
    inf.readEoln();   // end of line

    // No extra content
    inf.readEof();
    return 0;
}
