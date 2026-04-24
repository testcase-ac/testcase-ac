#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read test cases until EOF
    while (!inf.eof()) {
        setTestCase(++tc);
        // According to general rules: if number of test cases is not specified, assume ≤100000
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);

        // Read N (number of days), 1 ≤ N ≤ 100000
        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        // Read exactly N stock prices, each 1 ≤ p_i ≤ 100000
        inf.readInts(n, 1, 100000, "price");
        inf.readEoln();
    }

    // Ensure no extra data after reading all test cases
    inf.readEof();
    return 0;
}
