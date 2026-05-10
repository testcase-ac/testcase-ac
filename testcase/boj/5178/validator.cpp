#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We don't actually need to fully re-solve the problem for validation,
// but we must enforce all structural constraints (syntax, nesting depth,
// separators between test cases, etc.). We do NOT need to compute the
// time complexity itself, since that's what the contestants solve.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int tc = 1; tc <= K; ++tc) {
        setTestCase(tc);

        // Between test cases, there is a blank line (the statement says
        // "각 테스트 케이스는 빈 줄로 구분한다").
        if (tc > 1) {
            string blank = inf.readLine("[^]*", "blank");
            ensuref(blank.empty(),
                    "Expected a blank line between test cases, got: '%s'",
                    blank.c_str());
        }

        vector<string> lines;

        // Read lines of this program until "endprogram".
        while (true) {
            string line = inf.readLine("[^]*", "line");

            // No blank lines are allowed inside a program: the only blank
            // line is used as a separator between test cases.
            ensuref(!line.empty(),
                    "Unexpected empty line inside a program (only allowed between test cases)");

            lines.push_back(line);
            if (line == "endprogram") break;
        }

        int n = (int)lines.size();
        ensuref(n >= 1, "Program must contain at least 'endprogram'");
        ensuref(lines.back() == "endprogram",
                "Program must end with 'endprogram'");

        // For each line, classify it and (for loop) store its argument.
        vector<string> type(n); // "basic", "loop", "endloop", "endprogram"
        vector<string> arg(n);  // loop argument, if any

        // Stack for matching loops and tracking nesting depth.
        vector<int> loopStack;
        int maxDepth = 0;

        for (int i = 0; i < n; ++i) {
            const string &s = lines[i];

            if (s == "basic") {
                type[i] = "basic";
                // "basic" is allowed anywhere inside the program, including
                // top level (no enclosing loops). No extra constraint here.
            }
            else if (s == "endloop") {
                type[i] = "endloop";
                ensuref(!loopStack.empty(),
                        "endloop without matching loop at line %d", i + 1);
                loopStack.pop_back();
            }
            else if (s == "endprogram") {
                type[i] = "endprogram";
                ensuref(i == n - 1,
                        "endprogram must be the last line of the program");
                ensuref(loopStack.empty(),
                        "Some loops are not closed before endprogram");
            }
            else {
                // Must be "loop <arg>" with exactly one space.
                size_t pos = s.find(' ');
                ensuref(pos != string::npos,
                        "Invalid instruction at line %d: '%s'",
                        i + 1, s.c_str());

                string cmd = s.substr(0, pos);
                string a   = s.substr(pos + 1);

                ensuref(cmd == "loop",
                        "Unknown command '%s' at line %d",
                        cmd.c_str(), i + 1);
                // Ensure there is exactly one space: remaining part must
                // contain no spaces.
                ensuref(!a.empty(),
                        "Missing loop argument at line %d", i + 1);
                ensuref(a.find(' ') == string::npos,
                        "loop line must contain exactly one space at line %d",
                        i + 1);

                type[i] = "loop";
                arg[i]  = a;

                // Argument must be x, y, or a positive integer (no leading 0).
                if (a == "x" || a == "y") {
                    // ok
                } else {
                    // must be positive integer, canonical form.
                    for (char c : a)
                        ensuref(isdigit((unsigned char)c),
                                "Non-digit in loop integer argument at line %d",
                                i + 1);
                    ensuref(a[0] != '0',
                            "Loop integer argument must be positive without leading zeros at line %d",
                            i + 1);
                    // No upper bound on integer size is specified, and the
                    // validator does not need to evaluate it numerically.
                }

                loopStack.push_back(i);
                maxDepth = max(maxDepth, (int)loopStack.size());
                ensuref(maxDepth <= 50,
                        "Loop nesting depth exceeds 50 at line %d", i + 1);
            }
        }

        ensuref(loopStack.empty(),
                "Unclosed loops remain after processing the program");
    }

    inf.readEof();
}
