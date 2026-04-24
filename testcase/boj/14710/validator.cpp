#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two angles theta1 and theta2, each between 0 and 359 inclusive
    int theta1 = inf.readInt(0, 359, "theta1");
    inf.readSpace();
    int theta2 = inf.readInt(0, 359, "theta2");
    inf.readEoln();

    // No further constraints implied by the problem statement
    inf.readEof();
    return 0;
}
