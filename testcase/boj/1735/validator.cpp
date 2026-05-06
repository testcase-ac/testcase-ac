#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first fraction A/B
    int A = inf.readInt(1, 30000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 30000, "B");
    inf.readEoln();

    // Read second fraction C/D
    int C = inf.readInt(1, 30000, "C");
    inf.readSpace();
    int D = inf.readInt(1, 30000, "D");
    inf.readEoln();

    // No further constraints on input (output will handle reduction to lowest terms)
    inf.readEof();
    return 0;
}
