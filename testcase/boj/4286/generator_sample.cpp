#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string probabilityToken(int mode) {
    if (mode == 0) return "0";
    if (mode == 1) return "1";

    int digits = rnd.next(1, 7);
    int scale = 1;
    for (int i = 0; i < digits; ++i) scale *= 10;

    int value;
    if (mode == 2) {
        value = rnd.next(0, min(scale, 20));
    } else if (mode == 3) {
        value = rnd.next(max(0, scale - 20), scale);
    } else {
        value = rnd.next(0, scale);
    }

    if (value == 0) return "0";
    if (value == scale) return "1";

    string fractional = to_string(value);
    while ((int)fractional.size() < digits) fractional = "0" + fractional;
    return "0." + fractional;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(6, 18);
    vector<int> interestingN = {1, 2, 3, 4, 5, 10, 15, 24, 29, 30};

    for (int i = 0; i < cases; ++i) {
        int n;
        if (rnd.next(100) < 55) {
            n = rnd.any(interestingN);
        } else {
            n = rnd.next(1, 30);
        }

        string t = probabilityToken(rnd.next(0, 4));
        println(n, t);
    }

    println(0, 0);
    return 0;
}
