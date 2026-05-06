#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A and B
    int A = inf.readInt(1, 10000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 10000, "B");
    inf.readEoln();
    ensuref(A <= B, "Constraint violated: A(%d) must be <= B(%d)", A, B);

    // Second line: K and X
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    int X = inf.readInt(1, 10000, "X");
    inf.readEoln();

    // End of file
    inf.readEof();

    return 0;
}
