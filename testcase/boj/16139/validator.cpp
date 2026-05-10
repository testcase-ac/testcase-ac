#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: non-empty, only lowercase letters, length ≤ 200000
    string S = inf.readToken("[a-z]{1,200000}", "S");
    inf.readEoln();

    int n = (int)S.length();

    // Read number of queries q: 1 ≤ q ≤ 200000
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    // Read each query
    for (int i = 0; i < q; i++) {
        // alpha_i: a single lowercase letter
        string alpha = inf.readToken("[a-z]", "alpha_i");
        inf.readSpace();

        // l_i and r_i: 0 ≤ l_i, r_i < n
        int l = inf.readInt(0, n - 1, "l_i");
        inf.readSpace();
        int r = inf.readInt(0, n - 1, "r_i");
        inf.readEoln();

        // Ensure l_i ≤ r_i
        ensuref(l <= r,
                "Query %d has l_i > r_i: l_i=%d, r_i=%d",
                i, l, r);
    }

    inf.readEof();
    return 0;
}
