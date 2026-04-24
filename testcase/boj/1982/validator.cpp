#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: m f r c
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int f = inf.readInt(1, 100, "f");
    inf.readSpace();
    int r = inf.readInt(1, 100, "r");
    inf.readSpace();
    // c must be between 0 and min(m,f)
    int c = inf.readInt(0, 100, "c");
    inf.readEoln();
    ensuref(c <= min(m, f),
            "c must be <= min(m, f): c=%d, m=%d, f=%d", c, m, f);

    // Read r room descriptions
    for (int i = 0; i < r; i++) {
        int a = inf.readInt(1, 5, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 1000, "b_i");
        inf.readEoln();
        // No further global checks: solution will handle feasibility
    }

    inf.readEof();
    return 0;
}
