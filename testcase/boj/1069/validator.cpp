#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four integers X, Y, D, T according to problem constraints
    int X = inf.readInt(1, 1000, "X");
    inf.readSpace();
    int Y = inf.readInt(1, 1000, "Y");
    inf.readSpace();
    int D = inf.readInt(1, 10000, "D");
    inf.readSpace();
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // No additional global properties to check: you can always walk,
    // and jumps are independent. The answer always exists.

    inf.readEof();
    return 0;
}
