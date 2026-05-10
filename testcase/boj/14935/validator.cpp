#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the integer x as a token of digits
    string x = inf.readToken("[0-9]+", "x");
    // No extra characters on this line
    inf.readEoln();

    // Check length constraint: x <= 10^100
    // 10^100 is "1" followed by 100 zeros, length = 101
    const int MAX_LEN = 101;
    ensuref((int)x.size() <= MAX_LEN,
            "Number of digits of x must be at most %d, got %d", MAX_LEN, (int)x.size());

    // No leading zeros except for the single digit "0"
    if (x.size() > 1) {
        ensuref(x[0] != '0',
                "Leading zeros are not allowed, but x = \"%s\"", x.c_str());
    }

    // If x has exactly 101 digits, ensure x <= "1" + 100*'0'
    if ((int)x.size() == MAX_LEN) {
        string bound = "1";
        bound.append(100, '0');
        ensuref(x <= bound,
                "x must be <= 10^100, but \"%s\" > \"%s\"", x.c_str(), bound.c_str());
    }

    inf.readEof();
    return 0;
}
