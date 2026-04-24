#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Each line is either a bit-string with parity or the terminating "#"
        // Bit-string has 1 to 31 bits followed by 'e' or 'o'
        string s = inf.readLine("[01]{1,31}[eo]|#", "line");
        if (s == "#") {
            break;
        }
        // Count number of test cases; not specified, so assume ≤100000
        tc++;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);
        // No further checks needed: regex enforces bits-only prefix and parity char
    }

    inf.readEof();
    return 0;
}
