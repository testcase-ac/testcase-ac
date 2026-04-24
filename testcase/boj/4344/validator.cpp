#include "testlib.h"
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

// Parse a non-negative integer from string s, ensure it's in [minVal,maxVal].
static long long parseInt(const string &s, long long minVal, long long maxVal,
                          const char *name, int tc) {
    ensuref(!s.empty(), "Empty token for %s at test case %d", name, tc);
    // All chars must be digits
    for (char c : s) {
        ensuref(isdigit(c),
                "Non-digit character '%c' in %s at test case %d", c, name, tc);
    }
    // Convert safely
    __int128 val = 0;
    for (char c : s) {
        val = val * 10 + (c - '0');
        ensuref(val <= maxVal,
                "%s value %s exceeds maximum %lld at test case %d",
                name, s.c_str(), maxVal, tc);
    }
    ensuref(val >= minVal,
            "%s value %s below minimum %lld at test case %d",
            name, s.c_str(), minVal, tc);
    return (long long)val;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases C
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    for (int tc = 1; tc <= C; tc++) {
        setTestCase(tc);
        // Read the entire test-case line: digits and spaces only
        // space must be escaped in the regex
        string line = inf.readLine("[0-9\\ ]+", "test_case_line");

        // No leading or trailing spaces
        ensuref(!line.empty(), "Empty line at test case %d", tc);
        ensuref(line.front() != ' ',
                "Leading space in test case %d", tc);
        ensuref(line.back() != ' ',
                "Trailing space in test case %d", tc);
        // No consecutive spaces
        ensuref(line.find("  ") == string::npos,
                "Multiple consecutive spaces in test case %d", tc);

        // Split by spaces
        vector<string> tokens;
        {
            istringstream iss(line);
            string tok;
            while (iss >> tok) {
                tokens.push_back(tok);
            }
        }
        // Must have at least one token: N
        ensuref(!tokens.empty(),
                "No tokens found in test case %d", tc);

        // Parse N
        long long N = parseInt(tokens[0], 1, 1000, "N", tc);

        // Check that token count matches N+1 (one N and N scores)
        ensuref((long long)tokens.size() == N + 1,
                "Expected %lld scores but found %zu in test case %d",
                N, tokens.size() - 1, tc);

        // Parse each score
        for (int i = 1; i <= N; i++) {
            // token name "score"
            parseInt(tokens[i], 0, 100, "score", tc);
        }
    }

    inf.readEof();
    return 0;
}
