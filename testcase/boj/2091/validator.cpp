#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the five integers X, A, B, C, D with their constraints
    int X = inf.readInt(1, 10000, "X");
    inf.readSpace();
    int A = inf.readInt(0, 10000, "A");
    inf.readSpace();
    int B = inf.readInt(0, 10000, "B");
    inf.readSpace();
    int C = inf.readInt(0, 10000, "C");
    inf.readSpace();
    int D = inf.readInt(0, 10000, "D");

    // End of the only line of input
    inf.readEoln();
    // No extra data
    inf.readEof();
    return 0;
}
