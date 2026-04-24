#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the five integers A, B, C, D, E with strict whitespace rules
    int A = inf.readInt(1, 10000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 10000000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 10000000, "C");
    inf.readSpace();
    int D = inf.readInt(0, 10000000, "D");
    inf.readSpace();
    int E = inf.readInt(1, 10000000, "E");
    inf.readEoln();

    // Validate the only relational constraint among them: D ≤ E
    ensuref(D <= E, "Constraint violated: D (%d) must be <= E (%d)", D, E);

    inf.readEof();
    return 0;
}
