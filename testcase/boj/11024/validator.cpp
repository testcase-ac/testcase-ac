#include "testlib.h"
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (no explicit bound given, assume up to 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Read the entire line of this test case
        string line = inf.readLine("[^]+", "case_line");

        // Split by whitespace to get tokens
        vector<string> tokens;
        {
            istringstream iss(line);
            string tok;
            while (iss >> tok) {
                tokens.push_back(tok);
            }
        }

        // Check number of values N in this test case
        int N = (int)tokens.size();
        ensuref(N >= 1 && N <= 100,
                "Test case %d has %d values, but expected between 1 and 100",
                tc+1, N);

        // Validate each token
        for (int i = 0; i < N; ++i) {
            const string &s = tokens[i];
            // Must consist only of digits
            ensuref(!s.empty(),
                    "Empty token at test case %d, position %d", tc+1, i+1);
            for (char c : s) {
                ensuref(isdigit(c),
                        "Non-digit character '%c' in test case %d, token %d: \"%s\"",
                        c, tc+1, i+1, s.c_str());
            }
            // No leading zeros
            ensuref(s[0] != '0',
                    "Leading zero in test case %d, token %d: \"%s\"",
                    tc+1, i+1, s.c_str());
            // Length constraint: since value ≤ 10000, at most 5 digits
            ensuref((int)s.size() <= 5,
                    "Token too long in test case %d, token %d: \"%s\"",
                    tc+1, i+1, s.c_str());

            // Parse and check numeric range: 1 to 10000
            long long v = stoll(s);
            ensuref(v >= 1 && v <= 10000,
                    "Value out of allowed range [1,10000] in test case %d, token %d: %lld",
                    tc+1, i+1, v);
        }
    }

    inf.readEof();
    return 0;
}
