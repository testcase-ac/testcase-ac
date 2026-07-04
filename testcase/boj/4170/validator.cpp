#include "testlib.h"

#include <string>

using namespace std;

bool isValidDecimal(const string& token) {
    if (token == "0" || token == "1") {
        return true;
    }

    if (token.size() < 3 || token.size() > 8) {
        return false;
    }

    if (token[1] != '.') {
        return false;
    }

    if (token[0] != '0' && token[0] != '1') {
        return false;
    }

    int fractionalDigits = static_cast<int>(token.size()) - 2;
    if (fractionalDigits < 1 || fractionalDigits > 6) {
        return false;
    }

    for (int i = 2; i < static_cast<int>(token.size()); ++i) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
        if (token[0] == '1' && token[i] != '0') {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        string token = inf.readToken("[0-9A-Z.]{1,8}", "line");
        inf.readEoln();

        if (token == "END") {
            break;
        }

        ensuref(isValidDecimal(token),
                "test case %d is not a valid decimal number in [0, 1] with at most 6 fractional digits: %s",
                cases + 1, token.c_str());
        ++cases;
    }

    // CHECK: The statement says "several test cases" but gives no explicit
    // lower or upper bound. Accept an empty sequence and cap cases for practicality.
    ensuref(cases <= 100000, "too many test cases: %d", cases);

    inf.readEof();
}
