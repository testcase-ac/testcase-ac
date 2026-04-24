#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the two big integers A and B as tokens of digits
    string A = inf.readToken("[0-9]+", "A");
    inf.readSpace();
    string B = inf.readToken("[0-9]+", "B");
    inf.readEoln();

    // Check lengths
    ensuref((int)A.size() <= 300000,
            "Length of A is %d, but must be at most 300000", (int)A.size());
    ensuref((int)B.size() <= 300000,
            "Length of B is %d, but must be at most 300000", (int)B.size());

    // No leading zeros allowed, except the number "0" itself
    if (A.size() > 1) {
        ensuref(A[0] != '0',
                "A has leading zero: \"%s\"", A.c_str());
    }
    if (B.size() > 1) {
        ensuref(B[0] != '0',
                "B has leading zero: \"%s\"", B.c_str());
    }

    inf.readEof();
    return 0;
}
