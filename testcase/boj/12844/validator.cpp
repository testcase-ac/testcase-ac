#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 0, 100000, "A");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read M queries
    for (int qi = 0; qi < M; qi++) {
        // Read query type
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();

        // For both types, read i and j
        int i = inf.readInt(0, N - 1, "i");
        inf.readSpace();
        int j = inf.readInt(0, N - 1, "j");
        // Ensure i <= j
        ensuref(i <= j, "Query %d: invalid range i=%d > j=%d", qi + 1, i, j);

        if (t == 1) {
            // Type 1 has an extra k
            inf.readSpace();
            int k = inf.readInt(0, 100000, "k");
        }

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
