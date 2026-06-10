#include "testlib.h"

#include <algorithm>
#include <string>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxT = 1000;
    const int minDigits = 2;
    const int maxDigits = 16;

    int t = inf.readInt(1, maxT, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        std::string blank = inf.readLine("[^]*", "blank_line");
        ensuref(blank.empty(), "test case %d must be preceded by a blank line", tc);

        std::string s = inf.readToken("[0-9]{2,16}", "digits");
        inf.readEoln();

        ensuref((int)s.size() >= minDigits && (int)s.size() <= maxDigits,
                "test case %d digit string length must be between %d and %d, got %d",
                tc, minDigits, maxDigits, (int)s.size());

        bool allZero = std::all_of(s.begin(), s.end(), [](char ch) {
            return ch == '0';
        });
        ensuref((int)s.size() <= 2 || !allZero,
                "test case %d with more than 2 digits must not be all zeros", tc);
    }

    inf.readEof();
}
