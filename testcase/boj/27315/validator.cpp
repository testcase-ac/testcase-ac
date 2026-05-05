#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Next N lines: D_i, P_i, T_i, E_i
    // Constraints:
    // 1 ≤ D_i, P_i ≤ 1e9
    // T_i in {0,1}, E_i in {0,1}
    for (int i = 0; i < N; ++i) {
        long long D = inf.readLong(1LL, 1000000000LL, "D_i");
        inf.readSpace();
        long long P = inf.readLong(1LL, 1000000000LL, "P_i");
        inf.readSpace();
        int T = inf.readInt(0, 1, "T_i");
        inf.readSpace();
        int E = inf.readInt(0, 1, "E_i");
        inf.readEoln();

        // No further structural/global constraints are implied on these.
        (void)D;
        (void)P;
        (void)T;
        (void)E;
    }

    // Last line: HD, HP
    long long HD = inf.readLong(1LL, 1000000000LL, "HD");
    inf.readSpace();
    long long HP = inf.readLong(1LL, 1000000000LL, "HP");
    inf.readEoln();
    (void)HD;
    (void)HP;

    // No additional global properties (like guaranteed solvability or
    // bounds on answer) are stated that need to be enforced by simulation.

    inf.readEof();
}
