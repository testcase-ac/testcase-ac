#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(3, 100000, "M");
    inf.readEoln();

    int k = inf.readInt(1, 100, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int x = inf.readInt(2, n - 1, "X_i");
        inf.readSpace();
        int y = inf.readInt(2, m - 1, "Y_i");
        inf.readSpace();
        int maxRadius = min({x - 1, y - 1, n - x, m - y});
        int r = inf.readInt(1, maxRadius, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
