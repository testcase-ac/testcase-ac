#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A
    string A = inf.readToken("[0-9]+", "A");
    ensuref(A.size() <= 10000, "length of A is %d, exceeds 10000", (int)A.size());
    // Read the single space separator
    inf.readSpace();
    // Read B
    string B = inf.readToken("[0-9]+", "B");
    ensuref(B.size() <= 10000, "length of B is %d, exceeds 10000", (int)B.size());
    // End of line after B
    inf.readEoln();

    // No leading zeros except for the number zero itself
    ensuref(!(A.size() > 1 && A[0] == '0'),
            "A has leading zeros: \"%s\"", A.c_str());
    ensuref(!(B.size() > 1 && B[0] == '0'),
            "B has leading zeros: \"%s\"", B.c_str());

    // No extra content
    inf.readEof();
    return 0;
}
