#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Number of tiles M = N*N - floor(N/2)
    int M = N * N - N / 2;

    // Read each tile's left and right numbers
    for (int i = 1; i <= M; i++) {
        // Prepare names for clearer error messages
        char nameA[20], nameB[20];
        snprintf(nameA, sizeof(nameA), "A_%d", i);
        snprintf(nameB, sizeof(nameB), "B_%d", i);

        inf.readInt(1, 6, nameA);
        inf.readSpace();
        inf.readInt(1, 6, nameB);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
