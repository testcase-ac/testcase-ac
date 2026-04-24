#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 0 < n < 1000
    int n = inf.readInt(1, 999, "n");
    inf.readEoln();

    // Read the list of numbers, one per line, terminated by a zero.
    // Each number must satisfy: if non-zero, 0 < x < 10000.
    int idx = 0;
    while (true) {
        int x = inf.readInt(0, 9999, "x");
        inf.readEoln();
        if (x == 0) {
            // Terminator found; stop reading the list
            break;
        }
        // Validate the actual list values
        ensuref(x >= 1 && x <= 9999,
                "List element at index %d must be between 1 and 9999, but got %d",
                idx, x);
        idx++;
    }

    // No extra content after the terminating zero line
    inf.readEof();
    return 0;
}
