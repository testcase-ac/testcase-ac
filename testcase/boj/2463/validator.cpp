#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Prepare to check for unique weights
    const int WMAX = 100000;
    vector<char> seenW(WMAX + 1, 0);

    // Read edges
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readSpace();
        int w = inf.readInt(1, WMAX, "w_i");
        inf.readEoln();

        // No loops allowed
        ensuref(x != y,
                "Loop detected on edge %d: both endpoints are %d", i + 1, x);
        // Weights must be unique
        ensuref(!seenW[w],
                "Duplicate edge weight %d found at edge %d", w, i + 1);
        seenW[w] = 1;
    }

    // No extra data
    inf.readEof();
    return 0;
}
