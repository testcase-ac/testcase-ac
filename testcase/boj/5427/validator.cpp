#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 ≤ T ≤ 100
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read width w and height h
        int w = inf.readInt(1, 1000, "w");
        inf.readSpace();
        int h = inf.readInt(1, 1000, "h");
        inf.readEoln();

        bool hasAt = false;
        // Read the h map rows
        for (int i = 0; i < h; i++) {
            string row = inf.readLine("[^]+", "row");
            // Check row length
            ensuref((int)row.size() == w,
                    "Test case %d, row %d: expected width %d, found %d",
                    tc, i+1, w, (int)row.size());
            // Check each character
            for (int j = 0; j < w; j++) {
                char c = row[j];
                ensuref(c == '.' || c == '#' || c == '@' || c == '*',
                        "Test case %d, row %d, col %d: invalid character '%c'",
                        tc, i+1, j+1, c);
                if (c == '@') {
                    ensuref(!hasAt,
                            "Test case %d: multiple starting positions '@' found",
                            tc);
                    hasAt = true;
                }
            }
        }
        // Ensure exactly one '@'
        ensuref(hasAt,
                "Test case %d: no starting position '@' found", tc);
    }

    inf.readEof();
    return 0;
}
