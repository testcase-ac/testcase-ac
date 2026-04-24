#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read the cost matrix C of size N x N
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Name each entry for clear error messages
            char name[20];
            sprintf(name, "C_%d_%d", i+1, j+1);
            int cij = inf.readInt(0, 100000, name);
            if (j + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // Validate diagonal entries are zero
            if (i == j) {
                ensuref(cij == 0,
                        "Entry C[%d][%d] must be 0, but found %d",
                        i+1, j+1, cij);
            }
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
