#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Read M operations
    for (int i = 0; i < M; i++) {
        // Operation type: 0 for Sum, 1 for Modify
        int type = inf.readInt(0, 1, "type");
        inf.readSpace();

        // First argument: index i in [1, N]
        int idx = inf.readInt(1, N, "idx");
        inf.readSpace();

        // Second argument depends on type
        if (type == 0) {
            // Sum(i, j): j in [1, N]
            int j = inf.readInt(1, N, "j");
        } else {
            // Modify(i, k): k in [1, 100000]
            int k = inf.readInt(1, 100000, "k");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
