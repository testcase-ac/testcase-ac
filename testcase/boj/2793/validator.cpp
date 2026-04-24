#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B
    const long long MIN_A = 3;
    const long long MAX_B = 100000000000000000LL - 1; // B < 1e17
    long long A = inf.readLong(MIN_A, MAX_B, "A");
    inf.readSpace();
    long long B = inf.readLong(MIN_A, MAX_B, "B");
    inf.readEoln();

    // Validate ordering
    ensuref(A < B, "A must be less than B, but got A = %lld, B = %lld", A, B);

    // End of file
    inf.readEof();
    return 0;
}
