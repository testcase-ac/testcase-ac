#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int c = inf.readInt(1, n, "c");
    inf.readEoln();

    vector<bool> seen(c + 1, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int color = inf.readInt(1, c, "a_i");
        seen[color] = true;
    }
    inf.readEoln();

    for (int color = 1; color <= c; ++color) {
        ensuref(seen[color], "color %d does not appear", color);
    }

    inf.readEof();
}
