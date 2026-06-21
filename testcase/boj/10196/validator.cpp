#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int h = inf.readInt(1, 20, "h");
        inf.readSpace();
        int w = inf.readInt(1, 20, "w");
        inf.readEoln();

        for (int i = 0; i < h; ++i) {
            string row = inf.readToken("[XO]{1,20}", "row");
            ensuref(static_cast<int>(row.size()) == w,
                    "row %d length is %d, expected %d", i + 1,
                    static_cast<int>(row.size()), w);
            inf.readEoln();
        }
    }

    inf.readEof();
}
