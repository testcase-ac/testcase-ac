#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, d, k, c
    int N = inf.readInt(2, 3000000, "N");
    inf.readSpace();
    int d = inf.readInt(2, 3000, "d");
    inf.readSpace();
    int k = inf.readInt(2, 3000, "k");
    inf.readSpace();
    int c = inf.readInt(1, d, "c");
    inf.readEoln();

    // Validate implied constraint k <= N
    ensuref(k <= N, "k (%d) must be <= N (%d)", k, N);

    // Read the N sushi types, one per line
    for (int i = 0; i < N; i++) {
        inf.readInt(1, d, "a_i");
        inf.readEoln();
    }

    // End of file
    inf.readEof();
    return 0;
}
