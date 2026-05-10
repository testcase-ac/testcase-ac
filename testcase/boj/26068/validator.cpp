#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of gifticons
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read whole token like D-123 (no spaces)
        string s = inf.readToken("[^ \t\r\n]+", "gifticon_i");
        inf.readEoln();

        // Must start with "D-"
        ensuref(s.size() >= 3 && s[0] == 'D' && s[1] == '-',
                "Line %d: token must start with \"D-\", got \"%s\"",
                i + 2, s.c_str());

        // Extract numeric part
        string num = s.substr(2);
        // Must be non-empty
        ensuref(!num.empty(),
                "Line %d: missing number after \"D-\" in \"%s\"",
                i + 2, s.c_str());

        // Canonical decimal form: no leading '+', no leading zeros unless "0"
        // But constraint says 1 <= x_i <= 365, so leading '0' is always invalid
        for (char c : num) {
            ensuref('0' <= c && c <= '9',
                    "Line %d: non-digit character '%c' in number part of \"%s\"",
                    i + 2, c, s.c_str());
        }
        ensuref(num[0] != '0',
                "Line %d: leading zero in number part \"%s\" not allowed",
                i + 2, num.c_str());

        // Parse and check range 1..365
        long long x = 0;
        for (char c : num) {
            x = x * 10 + (c - '0');
            ensuref(x <= 365,
                    "Line %d: number exceeds upper bound 365 in \"%s\"",
                    i + 2, s.c_str());
        }
        ensuref(1 <= x && x <= 365,
                "Line %d: x_i out of range [1,365], got %lld",
                i + 2, x);
    }

    inf.readEof();
}
