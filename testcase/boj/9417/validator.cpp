#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases N: 1 < N < 100 => 2 <= N <= 99
    int N = inf.readInt(2, 99, "N");
    inf.readEoln();

    // Process each test case
    for (int tc = 1; tc <= N; ++tc) {
        // Read the entire line for this test case
        string line = inf.readLine("[^]+", "line");

        // Split by whitespace
        istringstream iss(line);
        vector<string> tokens;
        string tok;
        while (iss >> tok) {
            tokens.push_back(tok);
        }

        // M must satisfy 1 < M < 100 => 2 <= M <= 99
        int M = (int)tokens.size();
        ensuref(M >= 2 && M <= 99,
                "Test case %d: number of integers M = %d is out of bounds [2,99]", 
                tc, M);

        // Validate each token is a positive 32-bit signed integer
        for (int i = 0; i < M; ++i) {
            const string &s = tokens[i];
            // Non-empty
            ensuref(!s.empty(),
                    "Test case %d, token %d: empty token", tc, i+1);
            // Digits only
            for (char c : s) {
                ensuref(isdigit(c),
                        "Test case %d, token %d: '%s' contains non-digit '%c'",
                        tc, i+1, s.c_str(), c);
            }
            // No more than 10 digits (max 2147483647 has 10 digits)
            ensuref(s.size() <= 10,
                    "Test case %d, token %d: '%s' has more than 10 digits",
                    tc, i+1, s.c_str());

            // Parse value manually to avoid overflow
            long long val = 0;
            for (char c : s) {
                val = val * 10 + (c - '0');
            }
            // Must be positive integer and within 32-bit signed range
            ensuref(val >= 1 && val <= 2147483647LL,
                    "Test case %d, token %d: value %lld out of bounds [1,2147483647]",
                    tc, i+1, val);
        }
        // No extra checks on GCD answer existence or bounds are needed,
        // since M>=2 guarantees at least one pair.
    }

    inf.readEof();
    return 0;
}
