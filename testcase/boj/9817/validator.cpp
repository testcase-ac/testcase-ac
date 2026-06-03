#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int query_count = 0;
    while (true) {
        int n = inf.readInt(-1, 23, "n");
        inf.readEoln();

        if (n == -1) {
            break;
        }

        // CHECK: A necklace with n beads is treated as a nonempty object.
        ensuref(n >= 1, "n must be positive, got %d", n);
        ++query_count;
        // CHECK: The statement gives no explicit number of lines, so cap the stream at
        // the local default for an unspecified testcase count.
        ensuref(query_count <= 100000, "too many n values before terminator");
    }

    // CHECK: Reject a vacuous input that contains only the terminator.
    ensuref(query_count > 0, "at least one n value is required before -1");

    inf.readEof();
}
