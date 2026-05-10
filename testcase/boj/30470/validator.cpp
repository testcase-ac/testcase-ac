#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Track last inserted log length to enforce strict increase
    long long last_insert = 0; 
    // Since b >= 1 always, enforcing b > 0 for the first insertion is fine.

    for (int i = 1; i <= N; i++) {
        int type = inf.readInt(1, 2, "a_i");
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "b_i");
        inf.readEoln();

        if (type == 1) {
            // For insertion queries, x must be strictly increasing
            ensuref(x > last_insert,
                    "At query %d: inserted log length %d is not strictly greater than previous %lld",
                    i, x, last_insert);
            last_insert = x;
        }
        // For magic queries (type == 2), no additional validation is needed.
    }

    inf.readEof();
    return 0;
}
