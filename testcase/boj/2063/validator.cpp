#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

long long readRadius(int testCase, int index) {
    string token = inf.readToken("[^]{1,12}", "a_i");

    int dotCount = 0;
    int dotPos = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == '.') {
            ++dotCount;
            dotPos = i;
        } else {
            ensuref(isdigit((unsigned char)token[i]),
                    "radius %d in case %d contains a non-digit character: %s",
                    index, testCase, token.c_str());
        }
    }

    ensuref(dotCount <= 1, "radius %d in case %d has multiple decimal points: %s",
            index, testCase, token.c_str());
    ensuref(dotPos != 0, "radius %d in case %d has no integer part: %s",
            index, testCase, token.c_str());
    ensuref(dotPos != (int)token.size() - 1,
            "radius %d in case %d has no fractional digits: %s",
            index, testCase, token.c_str());

    string integerPart = dotPos == -1 ? token : token.substr(0, dotPos);
    string fractionalPart = dotPos == -1 ? "" : token.substr(dotPos + 1);
    ensuref(integerPart == "0" || integerPart[0] != '0',
            "radius %d in case %d has a leading zero: %s", index, testCase,
            token.c_str());
    ensuref(fractionalPart.size() <= 3,
            "radius %d in case %d has more than three fractional digits: %s",
            index, testCase, token.c_str());

    long long scaled = 0;
    for (char c : integerPart) scaled = scaled * 10 + (c - '0');
    scaled *= 1000;
    long long place = 100;
    for (char c : fractionalPart) {
        scaled += (c - '0') * place;
        place /= 10;
    }

    ensuref(1 <= scaled && scaled <= 10000000LL * 1000LL,
            "radius %d in case %d is outside (0, 10000000]: %s", index,
            testCase, token.c_str());
    return scaled;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the Korean statement and official sample use a leading testcase
    // count, while the English variant describes zero-terminated input.
    int t = inf.readInt(1, 30, "K");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            if (i > 1) inf.readSpace();
            readRadius(tc, i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
