#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: M (number of coins)
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Second line: M integers P_i (positions of coins)
    // Positions are between 1 and 1e9 inclusive
    vector<long long> P = inf.readLongs(M, 1LL, 1000000000LL, "P_i");
    inf.readEoln();

    // No additional global properties to check:
    // - Multiple coins can share the same position (explicitly allowed).
    // - All coins must be in [1, 1e9], already enforced above.
    // - Board size 1×1e10 just gives an upper bound; no need to check N explicitly.

    inf.readEof();
}
