#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int query_count = 0;
    while (true) {
        int n = inf.readInt(0, 32767, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++query_count;
        // CHECK: the statement says there can be many numbers but gives no count bound.
        ensuref(query_count <= 100000, "too many query numbers: %d", query_count);
        ensuref(n >= 4, "n must be at least 4, got %d", n);
        ensuref(n % 2 == 0, "n must be even, got %d", n);
    }

    inf.readEof();
}
