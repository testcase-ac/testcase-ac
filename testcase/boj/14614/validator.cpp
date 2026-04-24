#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B: 1 ≤ A, B ≤ 10^8
    int A = inf.readInt(1, 100000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100000000, "B");
    inf.readSpace();

    // Read C as a big integer: 1 ≤ C ≤ 10^100
    // We use a token regex to ensure it's a non-zero-leading decimal up to 101 digits
    string C = inf.readToken("[1-9][0-9]{0,100}", "C");

    // Now explicitly check that C ≤ 10^100.
    // 10^100 is "1" followed by 100 '0's, a 101-digit string.
    if ((int)C.size() == 101) {
        // Build the limit string "1" + 100 * '0'
        string limit = "1";
        limit += string(100, '0');
        ensuref(C == limit,
                "C must be at most 10^100, but got %s", C.c_str());
    }

    // End of line and end of file checks
    inf.readEoln();
    inf.readEof();

    return 0;
}
