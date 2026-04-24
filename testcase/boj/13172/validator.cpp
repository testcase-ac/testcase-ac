#include "testlib.h"
using namespace std;

static const int MOD = 1000000007;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of dice
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read each dice's parameters
    for (int i = 1; i <= M; i++) {
        // N_i: number of faces
        int Ni = inf.readInt(1, 1000000000, "N_i");
        inf.readSpace();
        // S_i: sum of face-values
        int Si = inf.readInt(1, 1000000000, "S_i");
        inf.readEoln();

        // The problem guarantees that the answer always exists,
        // which implies every Ni must be invertible mod MOD.
        // Since MOD is prime and Ni <= 1e9 < MOD, this always holds.
        // We assert it to reflect the guarantee.
        ensuref(Ni % MOD != 0,
                "N_i at line %d is divisible by %d, inverse does not exist", i + 1, MOD);
    }

    // No extra data
    inf.readEof();
    return 0;
}
