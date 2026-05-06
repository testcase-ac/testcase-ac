#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        // Read three integers per line
        int a = inf.readInt(0, 1000, "a");
        inf.readSpace();
        int b = inf.readInt(0, 1000, "b");
        inf.readSpace();
        int c = inf.readInt(0, 1000, "c");
        inf.readEoln();

        // Check for sentinel line "0 0 0"
        if (a == 0 && b == 0 && c == 0) {
            break;
        }

        // Non-sentinel lines must be positive
        ensuref(a >= 1, "Side a must be positive on non-sentinel line, got %d", a);
        ensuref(b >= 1, "Side b must be positive on non-sentinel line, got %d", b);
        ensuref(c >= 1, "Side c must be positive on non-sentinel line, got %d", c);

        // Count test cases, enforce limit
        cases++;
        ensuref(cases <= 100000, "Number of test cases exceeds 100000: %d", cases);
    }

    // No extra data after sentinel
    inf.readEof();
    return 0;
}
