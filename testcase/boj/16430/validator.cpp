#include "testlib.h"
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B on the first line
    int A = inf.readInt(1, 9, "A");
    inf.readSpace();
    int B = inf.readInt(1, 9, "B");
    inf.readEoln();

    // Validate A < B
    ensuref(A < B, "Constraint violated: A must be less than B, but A=%d, B=%d", A, B);

    // Validate that A and B are coprime
    int g = std::gcd(A, B);
    ensuref(g == 1, "Constraint violated: A and B must be coprime, but gcd(%d, %d) = %d", A, B, g);

    // No extra content
    inf.readEof();
    return 0;
}
