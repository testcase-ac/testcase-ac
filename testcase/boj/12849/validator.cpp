#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer D with constraint 1 ≤ D ≤ 100000
    int D = inf.readInt(1, 100000, "D");
    inf.readEoln();

    // No further constraints to validate; answer existence/graph etc.
    // are problem-internal and not stated as guarantees that must hold
    // for all inputs beyond bounds on D.

    inf.readEof();
}
