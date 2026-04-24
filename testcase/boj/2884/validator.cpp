#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read hours token: one or two digits
    string hs = inf.readToken("[0-9]{1,2}", "H");
    // Exactly one space separator
    inf.readSpace();
    // Read minutes token: one or two digits
    string ms = inf.readToken("[0-9]{1,2}", "M");
    // End of line after the two numbers
    inf.readEoln();

    // No leading zeros unless the number is exactly "0"
    ensuref(hs.size() == 1 || hs[0] != '0',
            "Leading zero in hour: '%s'", hs.c_str());
    ensuref(ms.size() == 1 || ms[0] != '0',
            "Leading zero in minute: '%s'", ms.c_str());

    // Parse to integers
    int h = 0;
    for (char c : hs) {
        h = h * 10 + (c - '0');
    }
    int m = 0;
    for (char c : ms) {
        m = m * 10 + (c - '0');
    }

    // Check ranges
    ensuref(0 <= h && h <= 23, "Hour out of range: %d", h);
    ensuref(0 <= m && m <= 59, "Minute out of range: %d", m);

    // No extra content
    inf.readEof();
    return 0;
}
