#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_count = 0;
    while (true) {
        // Read the next line (could be '-' or a bracket string)
        string line = inf.readLine("[^]+", "input line");

        // Check for end marker: one or more '-'
        bool is_end = true;
        for (char c : line) {
            if (c != '-') {
                is_end = false;
                break;
            }
        }
        if (is_end) {
            // After the end marker, there must be no more input
            inf.readEof();
            break;
        }

        // Otherwise, validate the line as a test case
        ++case_count;
        int len = line.length();
        ensuref(len >= 0 && len <= 2000, "Test case %d: String length %d is out of bounds [0,2000]", case_count, len);
        ensuref(len % 2 == 0, "Test case %d: String length %d is not even", case_count, len);

        for (int i = 0; i < len; ++i) {
            ensuref(line[i] == '{' || line[i] == '}', "Test case %d: Invalid character '%c' at position %d (1-based)", case_count, line[i], i+1);
        }
    }
}
