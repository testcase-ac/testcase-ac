#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Process queries
    int t1_count = 0;
    for (int q = 1; q <= M; q++) {
        // Read query type
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            // Type-1: update query "1 i v"
            int idx = inf.readInt(1, N, "i");
            inf.readSpace();
            int v = inf.readInt(1, 1000000, "v");
            inf.readEoln();

            t1_count++;
        } else {
            // Type-2: sum query "2 k i j"
            int k = inf.readInt(0, t1_count, "k");
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(1, N, "j");
            inf.readEoln();

            ensuref(i <= j,
                    "In query %d: i (%d) must be <= j (%d)", q, i, j);
        }
    }

    inf.readEof();
    return 0;
}
