#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first big integer A
    string A = inf.readToken("[0-9]+", "A");
    inf.readSpace();
    // Read second big integer B
    string B = inf.readToken("[0-9]+", "B");
    inf.readEoln();

    // Check lengths do not exceed 1,000,000 digits
    ensuref((int)A.length() <= 1000000,
            "Length of A exceeds 1,000,000: %d", (int)A.length());
    ensuref((int)B.length() <= 1000000,
            "Length of B exceeds 1,000,000: %d", (int)B.length());

    // Check for leading zeros (only "0" is allowed to start with '0')
    if (A.length() > 1) {
        ensuref(A[0] != '0',
                "Leading zero detected in A: \"%s\"", A.c_str());
    }
    if (B.length() > 1) {
        ensuref(B[0] != '0',
                "Leading zero detected in B: \"%s\"", B.c_str());
    }

    inf.readEof();
    return 0;
}
