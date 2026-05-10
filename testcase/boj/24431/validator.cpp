#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        set<string> seen;
        setTestCase(tc);

        // Read n, L, F
        int n = inf.readInt(2, 500, "n");
        inf.readSpace();
        int L = inf.readInt(1, 10, "L");
        inf.readSpace();
        int F = inf.readInt(1, L, "F"); // F must be <= L
        inf.readEoln();

        // Prepare regex for words of exact length L, uppercase only
        string wordRegex = "[A-Z]{" + to_string(L) + "," + to_string(L) + "}";

        // Read the n distinct words
        for (int i = 0; i < n; i++) {
            // Between words there must be exactly one space
            if (i > 0) inf.readSpace();
            string w = inf.readToken(wordRegex.c_str(), "W_i");
            // Check for duplicates
            ensuref(!seen.count(w),
                    "Duplicate word detected in test case %d: \"%s\"", tc, w.c_str());
            seen.insert(w);
        }
        inf.readEoln();
    }

    // No extra input
    inf.readEof();
    return 0;
}
