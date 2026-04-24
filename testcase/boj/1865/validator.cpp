#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int TC = inf.readInt(1, 5, "TC");
    inf.readEoln();

    for (int tc = 1; tc <= TC; tc++) {
        // We can set the test case number for clearer error messages
        setTestCase(tc);

        // Read N, M, W
        int N = inf.readInt(1, 500, "N");
        inf.readSpace();
        int M = inf.readInt(1, 2500, "M");
        inf.readSpace();
        int W = inf.readInt(1, 200, "W");
        inf.readEoln();

        // Read M roads: undirected edges with non-negative travel time
        for (int i = 0; i < M; i++) {
            int S = inf.readInt(1, N, "road_S");
            inf.readSpace();
            int E = inf.readInt(1, N, "road_E");
            inf.readSpace();
            // Although the statement does not explicitly bound road time T,
            // problems of this type usually have T up to 10000 and positive.
            int T = inf.readInt(1, 10000, "road_T");
            inf.readEoln();
            // No further global checks: loops or parallel edges are allowed
        }

        // Read W wormholes: directed edges with non-positive weight effect
        for (int i = 0; i < W; i++) {
            int S = inf.readInt(1, N, "wormhole_S");
            inf.readSpace();
            int E = inf.readInt(1, N, "wormhole_E");
            inf.readSpace();
            // Wormhole time reduction T: 0 <= T <= 10000
            int T = inf.readInt(0, 10000, "wormhole_T");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
