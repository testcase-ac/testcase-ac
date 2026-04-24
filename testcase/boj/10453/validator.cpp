#include "testlib.h"
#include <string>
using namespace std;

void check_good(const string &s, const char *name) {
    int n = s.size();
    // Check length bounds
    ensuref(n >= 2 && n <= 100000,
            "Length of %s is %d; expected between 2 and 100000", name, n);
    // Check balanced parentheses property: 'a' -> +1, 'b' -> -1
    int bal = 0;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        // We know via regex it's either 'a' or 'b'
        if (c == 'a') {
            bal++;
        } else {
            bal--;
        }
        ensuref(bal >= 0,
                "%s is not a good string: prefix ending at position %d has more b's than a's",
                name, i + 1);
    }
    ensuref(bal == 0,
            "%s is not a good string: total number of a's (%d) != number of b's",
            name, (int)count(s.begin(), s.end(), 'a'));
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read A
        string A = inf.readToken("[ab]+", "A");
        inf.readSpace();
        // Read B
        string B = inf.readToken("[ab]+", "B");
        inf.readEoln();

        // Check each is a good string
        check_good(A, "A");
        check_good(B, "B");
    }

    inf.readEof();
    return 0;
}
