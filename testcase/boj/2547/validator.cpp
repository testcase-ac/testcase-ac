#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_N = 100000;
    const long long MAX_C = (long long)1e18;

    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Between test cases, there is a blank line.
        // The statement only says "each test case is separated by a blank line",
        // so we:
        //  - allow an optional single blank line before the first test case;
        //  - require exactly one blank line between subsequent test cases;
        //  - do NOT allow more than one consecutive blank line anywhere.
        if (tc == 0) {
            // Optional single blank line after T and before first test.
            // Look at next character: if it's '\n', consume that empty line.
            // testlib doesn't have direct peek, so we emulate:
            // try to read a line that is either empty or starts with a digit / '-'.
            // But we must remain whitespace-strict, so we instead:
            // - check if next char is '\n' using readChar + unreadChar,
            //   however testlib does not expose unreadChar.
            // Simpler: try to read a line; if it's empty, treat as blank;
            // if not empty, interpret it as N, but then we have already
            // consumed it incorrectly. So we cannot safely "peek" this way.
            //
            // Therefore, we choose the following strict rule compatible
            // with samples:
            // - allow either:
            //     * a blank line followed by N, or
            //     * N directly
            //
            // We implement this by trying to read N via readInt; if the
            // next token is on the same line as T, testlib will handle that.
            // But sample clearly has a newline after T, so N starts at a new line.
            //
            // To distinguish optional blank line, we:
            //   1) read a line (could be empty or contain N),
            //   2) if it's empty, that's the optional blank, then read N normally
            //      from the next line using readInt;
            //   3) if it's non-empty, it must be just N with no extra spaces.
            //
            // Step 1:
            string firstLine = inf.readLine("[^]*", "maybe_blank_or_N");
            if (firstLine.empty()) {
                // blank separator before first test; now read N normally
                int N = inf.readInt(1, MAX_N, "N");
                inf.readEoln();
                for (int i = 0; i < N; ++i) {
                    long long c = inf.readLong(0LL, MAX_C, "c_i");
                    inf.readEoln();
                }
            } else {
                // This line must be exactly N, with no leading/trailing spaces.
                // Validate integer format and range manually.
                // Use testlib's string-to-long-long with ensuref on format.
                // We'll reuse testlib's parsing by creating a local InStream
                // is not allowed; instead, check with our own logic.
                // But we don't need full re-parsing if we enforce that it
                // contains only digits and no leading zeros (except "0"),
                // and then convert with standard stoll guarded by ensure.
                string s = firstLine;
                // Check canonical decimal integer form for positive int.
                ensuref(!s.empty(), "N line is empty for test case %d", tc + 1);
                // No '+' or '-' allowed; only digits.
                for (char ch : s) {
                    ensuref(ch >= '0' && ch <= '9',
                            "N must be a positive integer for test case %d", tc + 1);
                }
                // No leading zero unless single '0'
                ensuref(!(s.size() > 1 && s[0] == '0'),
                        "N has leading zeros in test case %d", tc + 1);
                // Now convert to integer and range-check
                long long Nll = 0;
                for (char ch : s) {
                    int d = ch - '0';
                    ensuref(Nll <= (long long)MAX_N, "N is too large in test case %d", tc + 1);
                    Nll = Nll * 10 + d;
                }
                ensuref(1 <= Nll && Nll <= MAX_N,
                        "N out of bounds [1, %d] in test case %d", MAX_N, tc + 1);
                int N = (int)Nll;

                // Now read N candy counts, one per line.
                for (int i = 0; i < N; ++i) {
                    long long c = inf.readLong(0LL, MAX_C, "c_i");
                    inf.readEoln();
                }
            }
        } else {
            // For tc > 0, there must be exactly one empty line before N.
            string blank = inf.readLine("[^]*", "blank_line");
            ensuref(blank.empty(),
                    "Expected exactly one empty line between test cases (before test case %d)",
                    tc + 1);

            int N = inf.readInt(1, MAX_N, "N");
            inf.readEoln();
            for (int i = 0; i < N; ++i) {
                long long c = inf.readLong(0LL, MAX_C, "c_i");
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
