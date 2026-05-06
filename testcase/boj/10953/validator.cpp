#include "testlib.h"
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T: since the statement does not specify an upper bound,
    // we assume 1 <= T <= 100000.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 0; i < T; i++) {
        // Read the entire line for the test case
        string line = inf.readLine("[^]+", "line");

        // No spaces or tabs allowed in the line
        ensuref(line.find(' ') == string::npos && line.find('\t') == string::npos,
                "Line %d: contains whitespace characters: '%s'", i+1, line.c_str());

        // There must be exactly one comma separating A and B
        int comma_cnt = count(line.begin(), line.end(), ',');
        ensuref(comma_cnt == 1,
                "Line %d: expected exactly one comma, found %d in '%s'", i+1, comma_cnt, line.c_str());

        // Split at the comma
        size_t pos = line.find(',');
        string a_str = line.substr(0, pos);
        string b_str = line.substr(pos + 1);

        // Both parts must be non-empty
        ensuref(!a_str.empty(),
                "Line %d: missing A before comma in '%s'", i+1, line.c_str());
        ensuref(!b_str.empty(),
                "Line %d: missing B after comma in '%s'", i+1, line.c_str());

        // Each part must consist solely of digits
        for (char c : a_str) {
            ensuref(isdigit(c),
                    "Line %d: non-digit character '%c' in A part '%s'", i+1, c, a_str.c_str());
        }
        for (char c : b_str) {
            ensuref(isdigit(c),
                    "Line %d: non-digit character '%c' in B part '%s'", i+1, c, b_str.c_str());
        }

        // Parse numeric values and check 0 < A, B < 10
        long long A = 0;
        for (char c : a_str) {
            A = A * 10 + (c - '0');
        }
        long long B = 0;
        for (char c : b_str) {
            B = B * 10 + (c - '0');
        }

        ensuref(A > 0 && A < 10,
                "Line %d: A must be between 1 and 9 inclusive, got %lld in '%s'", i+1, A, line.c_str());
        ensuref(B > 0 && B < 10,
                "Line %d: B must be between 1 and 9 inclusive, got %lld in '%s'", i+1, B, line.c_str());
    }

    inf.readEof();
    return 0;
}
