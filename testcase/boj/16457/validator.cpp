#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 2 * n, "skill");
        }
        // CHECK: The statement says each quest lists k skill names, but does not
        // explicitly require the k numbers in one quest to be distinct.
        inf.readEoln();
    }

    inf.readEof();
}
