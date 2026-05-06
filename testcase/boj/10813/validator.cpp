#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read M swap operations
    for (int k = 1; k <= M; k++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();

        // Validate that i <= j as per problem statement
        ensuref(i <= j,
                "Swap #%d has i > j: i = %d, j = %d; must satisfy i <= j",
                k, i, j);
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
