#include "testlib.h"
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "k");
    inf.readEoln();

    // Read intervals
    // We must ensure 0 ≤ a < b ≤ 1e9, intervals sorted by (a, b) strictly increasing and distinct.
    int prev_a = -1, prev_b = -1;
    for (int i = 0; i < n; i++) {
        int a = inf.readInt(0, 1000000000, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 1000000000, "b_i");
        inf.readEoln();

        ensuref(a < b,
                "Interval %d is invalid: left endpoint %d is not less than right endpoint %d",
                i+1, a, b);

        if (i > 0) {
            bool strictly_after = (a > prev_a) || (a == prev_a && b > prev_b);
            ensuref(strictly_after,
                    "Intervals are not strictly sorted or duplicate at index %d: "
                    "previous interval = (%d, %d), current = (%d, %d)",
                    i, prev_a, prev_b, a, b);
        }
        prev_a = a;
        prev_b = b;
    }

    // Read visit sequence of length k: indices between 1 and n
    vector<int> visits = inf.readInts(k, 1, n, "visit_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
