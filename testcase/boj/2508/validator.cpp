#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; ++tc) {
        setTestCase(tc + 1);

        // Between test cases, there is exactly one blank line.
        // "Each test case is separated by a blank line."
        // That means:
        // - After t on the first line, there is a blank line before the first test case.
        // - Between test cases, there is one empty line.
        // The example: "1\n\n5 4\n..." confirms there's a blank line before the first test case too.
        //
        // So: for every test case, read exactly one empty line before r c.
        {
            string blank = inf.readLine("[^]*", "blank_line");
            ensuref(blank.empty(),
                    "Expected a blank (empty) line before test case %d, but it is not empty",
                    tc + 1);
        }

        int r = inf.readInt(1, 400, "r");
        inf.readSpace();
        int c = inf.readInt(1, 400, "c");
        inf.readEoln();

        vector<string> grid(r);
        for (int i = 0; i < r; ++i) {
            // Read a row: exactly c characters, only from ".o<>v^"
            grid[i] = inf.readLine("[.o<>v^]{1,400}", "row");
            ensuref((int)grid[i].size() == c,
                    "Row %d length mismatch: expected %d, got %d",
                    i + 1, c, (int)grid[i].size());
        }

        // No extra global guarantees need to be enforced by the validator beyond format
        // and character set. Counting candies is purely solution logic and not a promised
        // global property, so we do not enforce anything using that.
    }

    inf.readEof();
}
