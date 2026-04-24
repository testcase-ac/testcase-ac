#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There must be exactly 10 lines of input, each with two integers a_i and b_i.
    for (int i = 0; i < 10; i++) {
        int a = inf.readInt(1, 20, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, 20, "b_i");
        // Ensure the interval is valid: a <= b
        ensuref(a <= b, "Invalid interval on line %d: a_i (%d) > b_i (%d)", i + 1, a, b);
        inf.readEoln();
    }

    // No extra data after the 10 lines
    inf.readEof();
    return 0;
}
