#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound K or program length. These caps keep
    // accepted inputs within a practical text size without adding semantic
    // restrictions to the simplified language.
    const int MAX_K = 100000;
    const int MAX_PROGRAM_LINES = 1000000;
    const int MAX_LINE_LENGTH = 100000;
    const long long MAX_TOTAL_CHARS = 9000000;

    int K = inf.readInt(1, MAX_K, "K");
    inf.readEoln();

    int totalProgramLines = 0;
    long long totalChars = 0;

    for (int tc = 1; tc <= K; ++tc) {
        setTestCase(tc);

        if (tc > 1) {
            string blank = inf.readLine("[^]*", "blank");
            ensuref(blank.empty(),
                    "Expected a blank line between test cases, got: '%s'",
                    blank.c_str());
        }

        vector<string> lines;

        while (true) {
            string line = inf.readLine("[^]*", "line");
            ++totalProgramLines;
            totalChars += (long long)line.size() + 1;
            ensuref(totalProgramLines <= MAX_PROGRAM_LINES,
                    "Too many program lines across all test cases");
            ensuref((int)line.size() <= MAX_LINE_LENGTH,
                    "Program line is too long at test case %d", tc);
            ensuref(totalChars <= MAX_TOTAL_CHARS,
                    "Program text is too large across all test cases");

            ensuref(!line.empty(),
                    "Unexpected empty line inside a program (only allowed between test cases)");

            lines.push_back(line);
            if (line == "endprogram") break;
        }

        int n = (int)lines.size();
        ensuref(n >= 1, "Program must contain at least 'endprogram'");
        ensuref(lines.back() == "endprogram",
                "Program must end with 'endprogram'");

        vector<int> loopStack;
        int maxDepth = 0;

        for (int i = 0; i < n; ++i) {
            const string &s = lines[i];

            if (s == "basic") {
                continue;
            }
            else if (s == "endloop") {
                ensuref(!loopStack.empty(),
                        "endloop without matching loop at line %d", i + 1);
                loopStack.pop_back();
            }
            else if (s == "endprogram") {
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

                if (a == "x" || a == "y") {
                } else {
                    for (char c : a)
                        ensuref(isdigit((unsigned char)c),
                                "Non-digit in loop integer argument at line %d",
                                i + 1);
                    ensuref(a[0] != '0',
                            "Loop integer argument must be positive without leading zeros at line %d",
                            i + 1);
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
