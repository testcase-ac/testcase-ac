#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read L, R, C (allow 0 only for sentinel)
        int L = inf.readInt(0, 30, "L");
        inf.readSpace();
        int R = inf.readInt(0, 30, "R");
        inf.readSpace();
        int C = inf.readInt(0, 30, "C");
        inf.readEoln();

        // Check for sentinel
        if (L == 0 && R == 0 && C == 0) {
            break;
        }
        // Non-sentinel: dimensions must be at least 1
        ensuref(L >= 1, "Test case %d: L must be between 1 and 30, found %d", tc+1, L);
        ensuref(R >= 1, "Test case %d: R must be between 1 and 30, found %d", tc+1, R);
        ensuref(C >= 1, "Test case %d: C must be between 1 and 30, found %d", tc+1, C);

        // Count test cases
        tc++;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: reached %d", tc);
        setTestCase(tc);

        int countS = 0, countE = 0;
        // Read L floors
        for (int l = 0; l < L; l++) {
            // Each floor has R rows
            string pattern = "[.#SE]{" + to_string(C) + "}";
            for (int i = 0; i < R; i++) {
                string row = inf.readToken(pattern, "row");
                inf.readEoln();
                // Count S and E
                for (char ch : row) {
                    if (ch == 'S') countS++;
                    else if (ch == 'E') countE++;
                }
            }
            // After each floor (including the last), exactly one blank line
            inf.readEoln();
        }

        // Exactly one 'S' and one 'E' per test case
        ensuref(countS == 1, "Test case %d: expected exactly one 'S', found %d", tc, countS);
        ensuref(countE == 1, "Test case %d: expected exactly one 'E', found %d", tc, countE);
    }

    // No extra content after sentinel
    inf.readEof();
    return 0;
}
