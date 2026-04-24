#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions and number of queries
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 5000, "M");
    inf.readSpace();
    int Q = inf.readInt(0, 200000, "Q");
    inf.readEoln();

    // Process each query line
    for (int i = 0; i < Q; i++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // Seed planting operation: 1 x1 y1 x2 y2 d
            inf.readSpace();
            int x1 = inf.readInt(1, N, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, M, "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, N, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, M, "y2");
            inf.readSpace();
            // d can be negative
            int d  = inf.readInt(-1000000000, 1000000000, "d");
            inf.readEoln();
            // Check ordering constraints
            ensuref(x1 <= x2, "Query %d: require x1 <= x2, got x1=%d, x2=%d", i+1, x1, x2);
            ensuref(y1 <= y2, "Query %d: require y1 <= y2, got y1=%d, y2=%d", i+1, y1, y2);
        } else {
            // Sum query: 2 x y
            inf.readSpace();
            int x = inf.readInt(1, N, "x");
            inf.readSpace();
            int y = inf.readInt(1, M, "y");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
