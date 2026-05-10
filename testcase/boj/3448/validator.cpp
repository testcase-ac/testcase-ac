#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_LINE_LEN = 100;
    const int MAX_LINES_PER_CASE = 200;

    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        vector<string> lines;
        long long recognized = 0;
        long long allchars = 0;

        // Read at least one line for this test case
        while (true) {
            // Peek next char to decide if we reached blank line marking end of test
            int c = inf.curChar();
            // curChar can be '\n' only if there is an empty line; that's separator
            if (c == '\n') break;

            // Read a line (may be empty only if separator, which we already prevent)
            string line = inf.readLine("[^]*", "line");

            ensuref((int)line.size() <= MAX_LINE_LEN,
                    "Line length exceeds %d in test case %d", MAX_LINE_LEN, tc);

            lines.push_back(line);
            if ((int)lines.size() > MAX_LINES_PER_CASE) {
                ensuref(false, "Number of lines exceeds %d in test case %d",
                        MAX_LINES_PER_CASE, tc);
            }

            // Count characters: '#' means unrecognized, everything else recognized
            for (char ch : line) {
                ++allchars;
                if (ch != '#') ++recognized;
            }

            // If next char is newline, that can still be a non-separator
            // but the rule says blank line (only newline) separates cases.
            // We must check lookahead: if next is '\n', it is a blank line,
            // but our readLine already consumed to before '\n'. So now curChar is '\n'.
            // We'll break in outer logic after we handle separator below.
            if (inf.eof()) break;
            c = inf.curChar();
            if (c == '\n') break;
        }

        ensuref(!lines.empty(), "Test case %d must contain at least one non-empty line", tc);

        // After the case's lines, there must be exactly one blank line,
        // except after the last test case.
        if (tc < T) {
            // Current position should be at newline starting the blank line
            // readLine() will read empty string then consume EOLN.
            string blank = inf.readLine("[^]*", "blank");
            ensuref(blank.empty(),
                    "Separator line between test cases must be blank in test case %d", tc);
        } else {
            // For last test case, there should be no extra blank line mandated,
            // but the input format says "각 테스트 케이스의 다음에는 빈 줄이 한 칸씩 있다."
            // which implies even after last one there is a blank line.
            // We'll enforce one final blank line as well.
            if (!inf.eof()) {
                string blank = inf.readLine("[^]*", "final_blank");
                ensuref(blank.empty(),
                        "Separator line after last test case must be blank");
            }
        }

        // Additional semantic check: there must be at least one character total
        // (since lines are at least one, but they could be empty; statement implies
        // they are lines of characters, but we ensure non-zero total characters).
        ensuref(allchars > 0,
                "Test case %d must contain at least one character", tc);
    }

    inf.readEof();
}
