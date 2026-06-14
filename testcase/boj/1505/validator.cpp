#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives the upper bound N, M <= 8, but an N x M
    // board is the central input object, so both dimensions must be positive.
    int n = inf.readInt(1, 8, "n");
    inf.readSpace();
    int m = inf.readInt(1, 8, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[*.]{1,8}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), m);
    }

    inf.readEof();
}
