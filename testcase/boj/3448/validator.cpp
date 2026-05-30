#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_T = 100000;
    constexpr int MAX_LINE_LEN = 100;
    constexpr int MAX_LINES_PER_CASE = 200;

    int t = inf.readInt(1, MAX_T, "N");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int lineCount = 0;
        long long charCount = 0;

        while (true) {
            ensuref(!inf.eof(), "missing blank line after test case %d", tc);

            if (inf.curChar() == '\n') {
                inf.readEoln();
                break;
            }

            string line = inf.readLine("[^]*", "line");
            ensuref(!line.empty(), "empty text line in test case %d", tc);
            ensuref((int)line.size() <= MAX_LINE_LEN,
                    "line length exceeds %d in test case %d", MAX_LINE_LEN, tc);

            ++lineCount;
            ensuref(lineCount <= MAX_LINES_PER_CASE,
                    "number of lines exceeds %d in test case %d",
                    MAX_LINES_PER_CASE, tc);
            charCount += (int)line.size();
        }

        ensuref(lineCount >= 1, "test case %d must contain at least one line", tc);
        ensuref(charCount > 0, "test case %d must contain at least one character", tc);
    }

    inf.readEof();
}
