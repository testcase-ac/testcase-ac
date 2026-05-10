#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There must be exactly 3 lines of input, each with 4 integers (0 or 1).
    for (int i = 0; i < 3; i++) {
        // Read exactly 4 integers, each either 0 or 1.
        inf.readInts(4, 0, 1, "value");
        // After these 4 integers, there must be exactly one end-of-line.
        inf.readEoln();
    }
    // After the third line, we must be at EOF immediately.
    inf.readEof();

    return 0;
}
