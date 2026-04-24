#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We interpret each input line (except the last "#") as a test case.
    // By default, if there's no explicit test-case count, assume up to 100000 cases.
    int cnt = 0;
    while (true) {
        // Read a line of length 1 to 250 (any characters except newline).
        string line = inf.readLine("[^]{1,250}", "line");
        // If this line is exactly "#", it's the terminator.
        if (line == "#") {
            break;
        }
        // Count test cases
        cnt++;
        ensuref(cnt <= 100000,
                "Number of lines (test cases) exceeds limit: %d > 100000", cnt);
        // Each non-terminator line must contain at least one non-space character.
        bool has_non_space = false;
        for (char c : line) {
            if (c != ' ') {
                has_non_space = true;
                break;
            }
        }
        ensuref(has_non_space,
                "Line %d has no non-space character: '%s'", cnt, line.c_str());
    }

    // After reading the terminator line "#", we must have reached EOF exactly.
    inf.readEof();
    return 0;
}
