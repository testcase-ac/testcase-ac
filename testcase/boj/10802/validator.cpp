#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A
    string A = inf.readToken("[0-9]+", "A");
    // No leading zeros, must be >= 1
    ensuref(A[0] != '0', "A has leading zero or is zero: '%s'", A.c_str());
    // Length constraints: since B ≤ 10^100000, A can have at most 100001 digits
    ensuref((int)A.size() <= 100001, "length of A exceeds 100001: %d", (int)A.size());

    inf.readSpace();

    // Read B
    string B = inf.readToken("[0-9]+", "B");
    ensuref(B[0] != '0', "B has leading zero or is zero: '%s'", B.c_str());
    ensuref((int)B.size() <= 100001, "length of B exceeds 100001: %d", (int)B.size());

    // Enforce B ≤ 10^100000 exactly:
    if ((int)B.size() == 100001) {
        // Only 10^100000 has length 100001: '1' followed by 100000 '0's
        ensuref(B[0] == '1', "When B has length 100001, its first digit must be '1'");
        for (int i = 1; i < (int)B.size(); i++) {
            ensuref(B[i] == '0', "Invalid B: digit at position %d (0-based) must be '0' for B = 10^100000", i);
        }
    }

    inf.readEoln();

    // Ensure global constraint A ≤ B
    if (A.size() < B.size()) {
        // always okay
    } else if (A.size() > B.size()) {
        ensuref(false, "A is greater than B: A='%s', B='%s'", A.c_str(), B.c_str());
    } else {
        ensuref(A <= B, "A is greater than B: A='%s', B='%s'", A.c_str(), B.c_str());
    }

    inf.readEof();
    return 0;
}
