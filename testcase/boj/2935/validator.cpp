#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A: should be a positive integer, power of 10, up to 100 digits.
    string A = inf.readLine("[0-9]+", "A");
    int nA = A.size();
    ensuref(nA >= 1, "A must have at least 1 digit, got length %d", nA);
    ensuref(nA <= 100, "A must have at most 100 digits, got length %d", nA);
    // Must be of form '1' followed by zeros.
    ensuref(A[0] == '1', "A must start with '1' to be a power of 10, got '%s'", A.c_str());
    for (int i = 1; i < nA; i++) {
        ensuref(A[i] == '0', "A must be of form 10^k, but A[%d] = '%c' in \"%s\"", i, A[i], A.c_str());
    }

    // Read operator: must be exactly '+' or '*'
    string op = inf.readLine("[+*]", "operator");
    ensuref(op.size() == 1, "Operator line must be exactly one character '+' or '*', got \"%s\"", op.c_str());

    // Read B: same constraints as A.
    string B = inf.readLine("[0-9]+", "B");
    int nB = B.size();
    ensuref(nB >= 1, "B must have at least 1 digit, got length %d", nB);
    ensuref(nB <= 100, "B must have at most 100 digits, got length %d", nB);
    ensuref(B[0] == '1', "B must start with '1' to be a power of 10, got '%s'", B.c_str());
    for (int i = 1; i < nB; i++) {
        ensuref(B[i] == '0', "B must be of form 10^k, but B[%d] = '%c' in \"%s\"", i, B[i], B.c_str());
    }

    inf.readEof();
    return 0;
}
