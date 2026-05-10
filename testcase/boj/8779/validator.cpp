#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int Z = inf.readInt(1, 10, "Z");
    inf.readEoln();

    for (int test = 1; test <= Z; ++test) {
        // Read W, K, R
        int W = inf.readInt(1, 1000, "W");
        inf.readSpace();
        int K = inf.readInt(1, 1000, "K");
        inf.readSpace();
        int R = inf.readInt(1, 1000, "R");
        inf.readEoln();

        for (int i = 0; i < W; ++i) {
            // Read K grades for row i
            vector<int> row = inf.readInts(K, 1, 1000000, "g_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
