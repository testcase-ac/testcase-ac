#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int x = inf.readInt(0, 3, "x");
        inf.readSpace();
        int y = inf.readInt(0, 3, "y");
        inf.readEoln();

        if (x == 0 && y == 0) {
            break;
        }

        ensuref(x >= 1 && y >= 1, "non-terminating coordinates must be in [1, 3]: x=%d y=%d", x, y);
        ++cases;
        ensuref(cases < 16, "number of datasets must be less than 16");
        setTestCase(cases);

        int emptyCount = 0;
        for (int row = 1; row <= 3; ++row) {
            for (int col = 1; col <= 3; ++col) {
                string color = inf.readToken("[BWRE]", "color");
                if (color == "E") {
                    ++emptyCount;
                }

                if (col < 3) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
        ensuref(emptyCount == 1, "dataset %d must contain exactly one E, found %d", cases, emptyCount);
    }

    inf.readEof();
}
