#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int t = 0; t < T; ++t) {
        // Read x1, y1, x2, y2
        int x1 = inf.readInt(-1000, 1000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 1000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-1000, 1000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 1000, "y2");
        inf.readEoln();

        // No further constraints to check per problem statement.
        // All coordinates are within the pool, and y != 0, y <= 1000, all are integers.
    }

    inf.readEof();
}
