#include "testlib.h"
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10000000, "b");
    inf.readEoln();

    long long digitCount;
    if (a == 10) {
        digitCount = 1LL * b + 1;
    } else if (a == 100) {
        digitCount = 2LL * b + 1;
    } else if (a == 1000) {
        digitCount = 3LL * b + 1;
    } else if (a == 10000) {
        digitCount = 4LL * b + 1;
    } else {
        digitCount = static_cast<long long>(floorl(log10l(a) * b)) + 1;
    }
    string digits = to_string(digitCount);

    ensuref(digits.rfind("10000", 0) != 0 && digits.rfind("9999", 0) != 0,
            "digit count starts with an excluded prefix: %lld", digitCount);

    inf.readEof();
}
