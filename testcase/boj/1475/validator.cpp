#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the room number N as a whole line: must consist only of digits, no spaces.
    string s = inf.readLine("[0-9]+", "N");

    // No leading zeros allowed (since N >= 1).
    ensuref(!(s.size() > 1 && s[0] == '0'),
            "Leading zero in N: \"%s\"", s.c_str());

    // Length must be at most 7 (to allow up to "1000000").
    ensuref(s.size() <= 7,
            "Length of N is too large: %d digits", (int)s.size());

    // Parse and check numeric bounds: 1 <= N <= 1,000,000
    long long x = stoll(s);
    ensuref(1 <= x && x <= 1000000,
            "N is out of allowed range [1,1000000]: %lld", x);

    // No extra data after this line
    inf.readEof();
    return 0;
}
