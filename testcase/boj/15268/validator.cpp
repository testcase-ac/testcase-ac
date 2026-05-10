#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 501, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        // Read the line as a token (not as int, to check for leading zeros and digit count)
        string x = inf.readToken("[0-9]{7}", "x_j");
        inf.readEoln();

        // Check that all digits are non-zero
        for (int j = 0; j < 7; ++j) {
            ensuref(x[j] >= '1' && x[j] <= '9',
                "x_%d has a zero digit at position %d: %s", i, j+1, x.c_str());
        }
        // Check that there are no leading zeros (already checked by previous loop)
        // But also, ensure that the number does not start with '0'
        ensuref(x[0] != '0', "x_%d has a leading zero: %s", i, x.c_str());
    }

    inf.readEof();
}
