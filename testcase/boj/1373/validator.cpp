#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the binary number as a single token consisting only of '0' and '1'
    string s = inf.readToken("[01]+", "binary");
    inf.readEoln();

    // Length constraint: 1 <= length <= 1_000_000
    ensuref(1 <= (int)s.size() && (int)s.size() <= 1000000,
            "binary length must be in [1, 1000000], got %d", (int)s.size());

    // Canonical form for base-2 number:
    // - either exactly "0"
    // - or does not start with '0'
    if (s.size() > 1) {
        ensuref(s[0] == '1',
                "binary must be in canonical form: no leading zeros allowed, got '%s'",
                s.c_str());
    }

    inf.readEof();
}
