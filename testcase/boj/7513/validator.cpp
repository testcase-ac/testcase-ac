#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of words
        int m = inf.readInt(1, 50, "m");
        inf.readEoln();

        // Read m words, each non-empty, no spaces, length <= 5
        for (int i = 0; i < m; ++i) {
            string w = inf.readToken("[^ \t\r\n]{1,5}", "word");
            inf.readEoln();
            // No further restrictions specified (e.g., alphabet), so accept any non-whitespace chars
        }

        // Number of participants
        int n = inf.readInt(1, 200, "n");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            // First integer: k (number of words in password)
            int k = inf.readInt(1, 10, "k");
            if (k > 0) inf.readSpace();

            // Next k integers: indices of words, 0-based, in [0, m-1]
            for (int j = 0; j < k; ++j) {
                int idx = inf.readInt(0, m - 1, "idx");
                if (j + 1 < k)
                    inf.readSpace();
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
