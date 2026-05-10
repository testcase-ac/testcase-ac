#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T: number of teams
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read N: number of fans
        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        // Read S_i: speeds
        vector<int> S = inf.readInts(N, 0, 1000000000, "S_i");
        inf.readEoln();

        // Read C_i: directions, as a line of N characters, each 'A' or 'T', separated by spaces
        // The line should be exactly: N tokens, each "A" or "T", separated by single spaces, no trailing/leading spaces
        vector<string> C = inf.readTokens(N, "[AT]", "C_i");
        inf.readEoln();

        // No further checks needed, as readTokens(N, "[AT]", ...) ensures each token is exactly "A" or "T"
    }

    inf.readEof();
}
