#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B with constraints 1 ≤ A < B ≤ 1e9
    long long A = inf.readLong(1LL, 1000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000LL, "B");
    inf.readEoln();

    // Validate A < B
    ensuref(A < B, "A must be less than B, but A = %lld, B = %lld", A, B);

    // No more input
    inf.readEof();
    return 0;
}
