#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lines N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // For each line, read A_i, B_i, C_i
    for (int i = 0; i < N; i++) {
        long long A = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        inf.readSpace();
        long long B = inf.readLong(-1000000000LL, 1000000000LL, "B_i");
        inf.readSpace();
        long long C = inf.readLong(-1000000000LL, 1000000000LL, "C_i");
        inf.readEoln();

        // Ensure we have a valid line: not both A and B zero
        ensuref(!(A == 0 && B == 0),
                "Line %d is invalid: both A and B are zero (not a line)", 
                i + 1);
    }

    // Note: The problem statement guarantees "no three lines meet at a single point."
    // Checking that globally in O(N^3) or O(N^2) is infeasible for N up to 300k,
    // so we rely on the problem authors' guarantee here.

    inf.readEof();
    return 0;
}
