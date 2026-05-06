#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input n: 1 ≤ n ≤ 10^12
    inf.readLong(1LL, 1000000000000LL, "n");
    // Expect exactly one newline after n
    inf.readEoln();
    // No extra data after the single test
    inf.readEof();

    return 0;
}
