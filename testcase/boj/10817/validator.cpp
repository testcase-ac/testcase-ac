#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three integers A, B, C in [1, 100], separated by whitespace.
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // No further global constraints to check for this problem.
    inf.readEof();
    return 0;
}
