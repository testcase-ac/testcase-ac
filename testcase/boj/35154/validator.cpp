#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 5000, "T");
    inf.readEoln();

    vector<int> n = inf.readInts(t, 1, 5000, "N_i");
    inf.readEoln();

    for (int i = 1; i < t; ++i) {
        ensuref(n[i - 1] < n[i], "N_i must be strictly increasing: N_%d=%d, N_%d=%d",
                i, n[i - 1], i + 1, n[i]);
    }

    inf.readEof();
}
