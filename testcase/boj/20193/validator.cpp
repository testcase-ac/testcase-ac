#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readEoln();

    vector<int> colorCount(k + 1);
    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 250000, "x_i");
        inf.readSpace();
        inf.readInt(1, 250000, "y_i");
        inf.readSpace();
        int color = inf.readInt(1, k, "k_i");
        inf.readEoln();
        ++colorCount[color];
    }

    for (int color = 1; color <= k; ++color) {
        ensuref(colorCount[color] > 0, "color %d is missing", color);
    }

    inf.readEof();
    return 0;
}
