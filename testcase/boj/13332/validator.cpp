#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: m, n, p, p'
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int p = inf.readInt(1, n, "p");
    inf.readSpace();
    int p2 = inf.readInt(p, n, "p'");
    inf.readEoln();

    // Next n lines: q_i, q_i'
    for (int i = 1; i <= n; i++) {
        int qi = inf.readInt(1, m, "q_i");
        inf.readSpace();
        int qi2 = inf.readInt(1, m, "q_i'");
        ensuref(qi <= qi2,
                "On day %d: q_i (%d) must be <= q_i' (%d)", i, qi, qi2);
        inf.readEoln();
    }

    // Next m lines: each member's vacation plans
    for (int j = 1; j <= m; j++) {
        // k = number of plans, 0 <= k <= 20
        int k = inf.readInt(0, 20, "k_j");
        int last_r2 = 0;
        for (int i = 1; i <= k; i++) {
            inf.readSpace();
            // Read d_i, r_i, r_i'
            int d = inf.readInt(1, n, "d_j_i");
            inf.readSpace();
            int r1 = inf.readInt(1, n, "r_j_i");
            inf.readSpace();
            int r2 = inf.readInt(r1, n, "r'_j_i");
            // Validate the plan
            ensuref(r1 <= r2,
                    "Member %d plan %d: r_i (%d) must be <= r_i' (%d)",
                    j, i, r1, r2);
            ensuref(d <= r2 - r1 + 1,
                    "Member %d plan %d: d_i (%d) exceeds interval length %d",
                    j, i, d, (r2 - r1 + 1));
            ensuref(r1 > last_r2,
                    "Member %d plan %d: intervals must be strictly increasing and disjoint; previous r_i' = %d, this r_i = %d",
                    j, i, last_r2, r1);
            last_r2 = r2;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
