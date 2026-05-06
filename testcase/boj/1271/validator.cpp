#include "testlib.h"
#include <string>
using namespace std;

static void checkBigInteger(const string &s, const string &name) {
    // must be non-empty and all digits
    ensuref(!s.empty(), "%s is empty", name.c_str());
    for (char c : s) {
        ensuref(c >= '0' && c <= '9', "%s contains non-digit character: %c", name.c_str(), c);
    }
    // no leading zeros
    if (s.size() > 1) {
        ensuref(s[0] != '0', "%s has leading zeros", name.c_str());
    }
    // value <= 10^1000
    // 10^1000 is "1" followed by 1000 zeros, length 1001
    if ((int)s.size() > 1001) {
        ensuref(false, "%s has length %d > 1001", name.c_str(), (int)s.size());
    }
    if ((int)s.size() == 1001) {
        // must be exactly "1" + 1000 * '0'
        static const string LIM = string("1") + string(1000, '0');
        ensuref(s == LIM, "%s > 10^1000", name.c_str());
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m on one line
    string n = inf.readToken("[0-9]+", "n");
    inf.readSpace();
    string m = inf.readToken("[0-9]+", "m");
    inf.readEoln();

    // Validate big integers
    checkBigInteger(n, "n");
    checkBigInteger(m, "m");

    // m >= 1 (since 1 ≤ m ≤ n)
    ensuref(!(m.size() == 1 && m[0] == '0'), "m must be at least 1");

    // Compare m <= n
    if (m.size() < n.size()) {
        // OK
    } else if (m.size() > n.size()) {
        ensuref(false, "m (%s) > n (%s)", m.c_str(), n.c_str());
    } else {
        // same length
        ensuref(m <= n, "m (%s) > n (%s)", m.c_str(), n.c_str());
    }

    inf.readEof();
    return 0;
}
