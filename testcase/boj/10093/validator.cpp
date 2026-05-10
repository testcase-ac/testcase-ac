#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B
    long long A = inf.readLong(1LL, 1000000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000000000LL, "B");
    inf.readEoln();
    
    // Validate the difference constraint: |A - B| ≤ 100000
    long long diff = A > B ? A - B : B - A;
    ensuref(diff <= 100000LL,
            "Absolute difference between A and B must be at most 100000, but got %lld", diff);

    inf.readEof();
    return 0;
}
