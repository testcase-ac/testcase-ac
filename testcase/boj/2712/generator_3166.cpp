#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    // Possible units
    vector<string> units = {"kg", "lb", "l", "g"};
    // Hyper-parameter: choose exponent for max integer part (0 -> max 1, 1 -> max 10, etc.)
    int expMax = rnd.next(0, 3);
    int maxInt = 1;
    for (int i = 0; i < expMax; i++) maxInt *= 10;

    println(T);
    for (int i = 0; i < T; i++) {
        // Integer part
        int intPart = rnd.next(0, maxInt);
        // Fraction length 0 to 4
        int fracLen = rnd.next(0, 4);
        char buf[32];
        if (fracLen > 0) {
            int maxFrac = 1;
            for (int j = 0; j < fracLen; j++) maxFrac *= 10;
            int fracPart = rnd.next(0, maxFrac - 1);
            // Format with zero-padded fractional part
            sprintf(buf, "%d.%0*d", intPart, fracLen, fracPart);
        } else {
            // No fractional part
            sprintf(buf, "%d", intPart);
        }
        string valStr(buf);
        // Random unit
        string unit = rnd.any(units);
        println(valStr, unit);
    }
    return 0;
}
