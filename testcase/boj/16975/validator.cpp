#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Process queries
    bool hasType2 = false;
    for (int qi = 1; qi <= M; qi++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // Query type 1: "1 i j k"
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(1, N, "j");
            ensuref(i <= j,
                    "In query %d: i (%d) must be <= j (%d)", 
                    qi, i, j);
            inf.readSpace();
            int k = inf.readInt(-1000000, 1000000, "k");
            inf.readEoln();
        } else {
            // Query type 2: "2 x"
            hasType2 = true;
            inf.readSpace();
            int x = inf.readInt(1, N, "x");
            inf.readEoln();
        }
    }

    // Ensure at least one type-2 query exists
    ensuref(hasType2, "There must be at least one type-2 query");

    inf.readEof();
    return 0;
}
