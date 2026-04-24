#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three integers E, S, M with their specified bounds.
    int E = inf.readInt(1, 15, "E");
    inf.readSpace();
    int S = inf.readInt(1, 28, "S");
    inf.readSpace();
    int M = inf.readInt(1, 19, "M");
    inf.readEoln();

    // Given the cyclic ranges, for any (E,S,M) there is always a solution in [1, lcm(15,28,19)].
    // Since 15,28,19 are pairwise coprime, lcm = 15 * 28 * 19 = 7980.
    // The problem guarantees the answer exists and is non-negative, so no further global checks are required.

    inf.readEof();
    return 0;
}
