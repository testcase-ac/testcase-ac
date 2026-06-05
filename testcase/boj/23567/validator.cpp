#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    vector<int> count(k + 1);
    for (int i = 1; i <= n; ++i) {
        int color = inf.readInt(1, k, "color_i");
        inf.readEoln();
        ++count[color];
    }

    for (int color = 1; color <= k; ++color) {
        ensuref(count[color] > 0, "color %d does not appear", color);
    }

    inf.readEof();
}
