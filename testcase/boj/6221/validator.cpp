#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 20, "N");
    inf.readEoln();

    set<int> widths;
    set<int> breadths;
    for (int i = 0; i < n; ++i) {
        // CHECK: The statement omits numeric bounds for bale dimensions; use a
        // practical positive int-sized cap for testcase.ac inputs.
        int width = inf.readInt(1, 1000000000, "width");
        inf.readSpace();
        int breadth = inf.readInt(1, 1000000000, "breadth");
        inf.readEoln();

        ensuref(widths.insert(width).second,
                "duplicate width at bale %d: %d", i + 1, width);
        ensuref(breadths.insert(breadth).second,
                "duplicate breadth at bale %d: %d", i + 1, breadth);
    }

    inf.readEof();
}
