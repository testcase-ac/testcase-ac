#include "testlib.h"
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read the sequence of n words
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            // requires exactly one space between tokens
            inf.readSpace();
        }
        // read next word (anything except space)
        string s = inf.readToken("[^ ]+", "word");

        if (s != "mumble") {
            // must be all digits
            ensuref(!s.empty(), "Token %d is empty", i);
            for (int j = 0; j < (int)s.size(); j++) {
                ensuref(isdigit(s[j]),
                        "Non-digit character '%c' in token %d (%s)",
                        s[j], i, s.c_str());
            }
            // parse value and check range [0,10000]
            // stoll should not throw since it's all digits
            long long val = stoll(s);
            ensuref(0 <= val && val <= 10000,
                    "Integer at position %d (%lld) out of allowed range [0,10000]",
                    i, val);
        }
    }
    // after the nth token, there must be exactly a newline
    inf.readEoln();
    // and then immediately EOF
    inf.readEof();

    return 0;
}
