#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    inf.readInt(1, 100, "M");
    inf.readSpace();
    inf.readInt(2, 1000, "K");
    inf.readEoln();

    vector<int> digits = inf.readInts(n, 0, 9, "a_i");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(digits[i - 1] < digits[i],
                "digits must be strictly increasing: a_%d=%d, a_%d=%d",
                i, digits[i - 1], i + 1, digits[i]);
    }

    inf.readEof();
}
