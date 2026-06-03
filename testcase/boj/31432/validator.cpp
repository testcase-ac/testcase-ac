#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    vector<int> digits;
    for (int i = 0; i < n; ++i) {
        int digit = inf.readInt(0, 9, "d_i");
        digits.push_back(digit);
        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    for (int i = 1; i < n; ++i) {
        ensuref(digits[i - 1] < digits[i],
                "digits must be strictly increasing: d_%d=%d, d_%d=%d",
                i, digits[i - 1], i + 1, digits[i]);
    }

    inf.readEof();
}
