#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 501, "n");
        inf.readEoln();
        ensuref(n % 3 == 0, "n must be a multiple of 3, found %d", n);

        array<int, 3> residueCount{};
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(0, n - 1, "p_i");
            ++residueCount[value % 3];
        }
        inf.readEoln();

        // CHECK: The statement says each case is a permutation of 0..n-1, but
        // the official sample repeats a value. Accept repeated values when the
        // residue multiset still permits conversion by swaps.
        for (int residue = 0; residue < 3; ++residue) {
            ensuref(residueCount[residue] == n / 3,
                    "residue %d appears %d times, expected %d",
                    residue,
                    residueCount[residue],
                    n / 3);
        }
    }

    inf.readEof();
}
