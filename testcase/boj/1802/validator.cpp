#include "testlib.h"
#include <string>
#include <cmath>

using namespace std;

// Helper function to check if x is 2^N - 1 for N >= 1
bool is_two_pow_n_minus_1(int x) {
    // x+1 should be a power of two, and at least 2
    if (x < 1) return false;
    int y = x + 1;
    return (y & (y - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        string s = inf.readToken("[01]+", "folding_info");
        inf.readEoln();

        int len = s.length();
        ensuref(len < 3000, "Length of folding_info at test case %d is %d, which is not less than 3000", tc, len);
        ensuref(is_two_pow_n_minus_1(len), "Length of folding_info at test case %d is %d, which is not of the form 2^N-1 (N >= 1)", tc, len);

        // No leading zeros check needed, as string can start with '0' or '1'
        // All characters are checked by regex [01]+
    }

    inf.readEof();
}
