#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 2, "N");
        inf.readSpace();

        // A and B are floating-point numbers with exactly two decimals, in [-10.00, 10.00]
        // Read as tokens and validate format and range manually.
        auto readFixed2 = [&](const char* name) -> double {
            string tok = inf.readToken("[^ ]+", name);
            // Validate format: optional '-' then digits then '.' then exactly two digits
            // No leading '+', no extra characters
            // We'll check manually instead of complex regex.
            ensuref(!tok.empty(), "%s is empty", name);

            int pos = 0;
            bool neg = false;
            if (tok[pos] == '-') {
                neg = true;
                pos++;
                ensuref(pos < (int)tok.size(), "%s: '-' not followed by digits", name);
            }
            // integer part: at least one digit, no leading zeros unless single '0'
            int intStart = pos;
            while (pos < (int)tok.size() && isdigit(tok[pos])) pos++;
            int intEnd = pos;
            ensuref(intEnd > intStart, "%s: integer part missing", name);
            // leading zero check
            if (intEnd - intStart > 1) {
                ensuref(tok[intStart] != '0', "%s: leading zeros not allowed in integer part", name);
            }

            // must have '.', then exactly two digits
            ensuref(pos < (int)tok.size() && tok[pos] == '.', "%s: missing decimal point", name);
            pos++;
            ensuref(pos + 2 == (int)tok.size(), "%s: must have exactly two digits after decimal point", name);
            ensuref(isdigit(tok[pos]) && isdigit(tok[pos + 1]),
                    "%s: non-digit characters in fractional part", name);

            // Now parse as double and check range [-10.00, 10.00]
            double val = stod(tok);
            ensuref(val >= -10.00 - 1e-9 && val <= 10.00 + 1e-9,
                    "%s: value %f out of range [-10.00, 10.00]", name, val);
            return val;
        };

        double A = readFixed2("A");
        inf.readSpace();
        double B = readFixed2("B");
        inf.readEoln();

        vector<double> C(N);
        // second line: N floating-point numbers C_i, each with exactly two decimals and in [-10.00, 10.00]
        for (int i = 0; i < N; ++i) {
            const string varName = "C_" + to_string(i + 1);
            C[i] = readFixed2(varName.c_str());
            if (i + 1 < N) inf.readSpace();
        }
        inf.readEoln();

        // Check C_i are distinct
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                ensuref(fabs(C[i] - C[j]) > 1e-9,
                        "C_%d and C_%d must be distinct but both are %.10f",
                        i + 1, j + 1, C[i]);
            }
        }

        // There is no additional guaranteed global property (like existence of optimal path
        // with bounded answer) that must be enforced by simulating or computing here.
        // The constraints above fully reflect the problem statement.
    }

    inf.readEof();
}
