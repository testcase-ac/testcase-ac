#include "testlib.h"
#include <string>
using namespace std;

// Check if n is an automorphic number: n^2 ends with n
bool isSelfReplicating(int n) {
    long long sq = 1LL * n * n;
    string sN = to_string(n);
    string sSq = to_string(sq);
    if (sSq.size() < sN.size()) return false;
    return sSq.substr(sSq.size() - sN.size()) == sN;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Problem guarantees: we're just checking the condition in solutions,
        // but there is no statement guarantee like "answer always YES" or similar,
        // so we do not enforce anything extra here beyond bounds.
        // However, we may still verify that computation is safe and within range.
        long long sq = 1LL * N * N;
        ensuref(sq <= 1000000LL, "Overflow or unexpected large square for N=%d", N);

        // No further global constraints specified across test cases.
        // Do not check whether it's self-replicating here, as that's the task of the solution.
    }

    inf.readEof();
}
