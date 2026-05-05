#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the 6 integers
    int P1 = inf.readInt(1, 300, "P1");
    inf.readSpace();
    int P2 = inf.readInt(1, 300, "P2");
    inf.readSpace();
    int P3 = inf.readInt(1, 300, "P3");
    inf.readSpace();
    int X1 = inf.readInt(1, 300, "X1");
    inf.readSpace();
    int X2 = inf.readInt(1, 300, "X2");
    inf.readSpace();
    int X3 = inf.readInt(1, 300, "X3");
    inf.readEoln();

    // Check that Pi > Xi for i=1,2,3
    ensuref(P1 > X1, "P1 (%d) must be greater than X1 (%d)", P1, X1);
    ensuref(P2 > X2, "P2 (%d) must be greater than X2 (%d)", P2, X2);
    ensuref(P3 > X3, "P3 (%d) must be greater than X3 (%d)", P3, X3);

    inf.readEof();
}
