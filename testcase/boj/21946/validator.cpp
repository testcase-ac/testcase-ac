#include "testlib.h"

#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives upper bounds, but the described card and spell sets are nonempty.
    int n = inf.readInt(1, 60, "n");
    inf.readSpace();
    int m = inf.readInt(1, 24, "m");
    inf.readEoln();

    vector<uint64_t> spells(m);
    for (int i = 0; i < m; ++i) {
        int q = inf.readInt(1, n, "q");
        vector<bool> seen(n + 1, false);
        uint64_t mask = 0;

        for (int j = 0; j < q; ++j) {
            inf.readSpace();
            int a = inf.readInt(1, n, "a");
            ensuref(!seen[a], "card index %d appears more than once in spell %d", a, i + 1);
            seen[a] = true;
            mask ^= (1ULL << (a - 1));
        }

        spells[i] = mask;
        inf.readEoln();
    }

    uint64_t target = n == 64 ? ~0ULL : ((1ULL << n) - 1);
    bool solvable = false;
    uint64_t current = 0;
    int previousGray = 0;

    for (int subset = 0; subset < (1 << m); ++subset) {
        int gray = subset ^ (subset >> 1);
        if (subset > 0) {
            int changed = __builtin_ctz(static_cast<unsigned>(gray ^ previousGray));
            current ^= spells[changed];
        }
        if (current == target) {
            solvable = true;
            break;
        }
        previousGray = gray;
    }

    // CHECK: The output format has no impossible case, so valid inputs must have a solution.
    ensuref(solvable, "no subset of spells turns all cards face up");

    inf.readEof();
}
