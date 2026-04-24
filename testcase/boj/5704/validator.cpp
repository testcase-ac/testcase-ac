#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        // Read a full line (including possibly "*")
        string s = inf.readLine("[^]*", "line");
        caseCount++;

        // Check for terminating line
        if (s == "*") {
            break;
        }

        // Length constraints
        ensuref(!s.empty(),
                "Line %d is empty; each test case must be a non-empty sentence", caseCount);
        ensuref((int)s.size() <= 200,
                "Line %d is too long: %d characters (maximum is 200)", caseCount, (int)s.size());

        // No leading or trailing spaces
        ensuref(s.front() != ' ' && s.back() != ' ',
                "Line %d has leading or trailing spaces", caseCount);

        // Words separated by exactly one space, and only lowercase letters
        bool prevSpace = false;
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (c == ' ') {
                ensuref(!prevSpace,
                        "Line %d has consecutive spaces at position %d", caseCount, i);
                prevSpace = true;
            } else {
                ensuref(c >= 'a' && c <= 'z',
                        "Line %d has invalid character '%c' at position %d; only 'a'-'z' and spaces allowed",
                        caseCount, c, i);
                prevSpace = false;
            }
        }
    }

    // Check number of test cases (excluding the "*" line)
    ensuref(caseCount - 1 <= 100000,
            "Too many test cases: %d (maximum is 100000)", caseCount - 1);

    inf.readEof();
    return 0;
}
