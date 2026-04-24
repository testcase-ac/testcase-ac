#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 25, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, R, P, S
        int N = inf.readInt(1, 3, "N");
        inf.readSpace();
        int maxPlayers = 1 << N;
        int R = inf.readInt(0, maxPlayers, "R");
        inf.readSpace();
        int P = inf.readInt(0, maxPlayers, "P");
        inf.readSpace();
        int S = inf.readInt(0, maxPlayers, "S");
        inf.readEoln();

        // Global constraint: total players must be exactly 2^N
        ensuref(R + P + S == maxPlayers,
                "In test case %d: R+P+S must equal 2^N, but got %d+%d+%d != %d",
                tc, R, P, S, maxPlayers);
    }

    inf.readEof();
    return 0;
}
