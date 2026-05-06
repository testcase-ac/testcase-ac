#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of squares in the bottom row
    // Constraint: 1 ≤ n ≤ 10^9
    inf.readInt(1, 1000000000, "n");
    // Ensure exactly one newline after n
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
