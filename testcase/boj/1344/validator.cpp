#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A team's scoring probability (percentage)
    int pA = inf.readInt(0, 100, "p_A");
    inf.readEoln();

    // Read B team's scoring probability (percentage)
    int pB = inf.readInt(0, 100, "p_B");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
