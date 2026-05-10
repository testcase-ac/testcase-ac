#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read four integers: x1, y1, x2, y2
    int x1 = inf.readInt(0, 1000000, "x1");
    inf.readSpace();
    int y1 = inf.readInt(0, 1000000, "y1");
    inf.readSpace();
    int x2 = inf.readInt(0, 1000000, "x2");
    inf.readSpace();
    int y2 = inf.readInt(0, 1000000, "y2");
    inf.readEoln();

    // Check strict inequalities
    ensuref(x1 < x2, "x1 (%d) must be less than x2 (%d)", x1, x2);
    ensuref(y1 < y2, "y1 (%d) must be less than y2 (%d)", y1, y2);

    inf.readEof();
}
