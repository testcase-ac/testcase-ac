#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string decimalToken(int numerator, int digits) {
    if (numerator == 0) {
        return rnd.next(2) == 0 ? "0" : "0." + string(digits, '0');
    }

    int scale = 1;
    for (int i = 0; i < digits; ++i) {
        scale *= 10;
    }

    if (numerator == scale) {
        return rnd.next(2) == 0 ? "1" : "1." + string(digits, '0');
    }

    string fraction = to_string(numerator);
    if (static_cast<int>(fraction.size()) < digits) {
        fraction = string(digits - fraction.size(), '0') + fraction;
    }
    return "0." + fraction;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> cases = {
        "0",
        "1",
        "0.000001",
        "0.999999",
        "1.000000",
        "0.333333",
        "0.333334",
        "0.666666",
        "0.666667",
        "0.875",
    };

    int randomCases = rnd.next(8, 24);
    for (int i = 0; i < randomCases; ++i) {
        int digits = rnd.next(1, 6);
        int scale = 1;
        for (int j = 0; j < digits; ++j) {
            scale *= 10;
        }

        int mode = rnd.next(6);
        int numerator;
        if (mode == 0) {
            numerator = rnd.next(0, 3);
        } else if (mode == 1) {
            numerator = scale - rnd.next(0, 3);
        } else if (mode == 2) {
            numerator = scale / 3 + rnd.next(-2, 2);
        } else if (mode == 3) {
            numerator = (2 * scale) / 3 + rnd.next(-2, 2);
        } else {
            numerator = rnd.next(0, scale);
        }

        if (numerator < 0) {
            numerator = 0;
        }
        if (numerator > scale) {
            numerator = scale;
        }
        cases.push_back(decimalToken(numerator, digits));
    }

    shuffle(cases.begin(), cases.end());
    for (const string& token : cases) {
        println(token);
    }
    println("END");

    return 0;
}
