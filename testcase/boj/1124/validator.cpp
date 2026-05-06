#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B with strict whitespace handling
    int A = inf.readInt(2, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(2, 100000, "B");
    inf.readEoln();

    // A must not exceed B
    ensuref(A <= B, "A (%d) must be <= B (%d)", A, B);

    inf.readEof();
    return 0;
}
