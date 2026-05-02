#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read n and m
        int n = inf.readInt(1, 500, "n");
        inf.readSpace();
        int m = inf.readInt(1, 500, "m");
        inf.readEoln();

        int cnt_B = 0, cnt_W = 0;
        for (int i = 0; i < n; ++i) {
            std::string row = inf.readLine("[B.W]{"+to_string(m)+","+to_string(m)+"}", "pattern row");
            ensuref((int)row.size() == m, "Row %d: Expected length %d, got %d", i+1, m, (int)row.size());
            for (int j = 0; j < m; ++j) {
                char c = row[j];
                ensuref(c == 'B' || c == 'W' || c == '.', "Row %d, Col %d: Invalid character '%c'", i+1, j+1, c);
                if (c == 'B') ++cnt_B;
                if (c == 'W') ++cnt_W;
            }
        }
        // At least one 'B' or 'W' in the pattern
        ensuref(cnt_B + cnt_W >= 1, "Testcase %d: Pattern must contain at least one 'B' or 'W'", tc+1);

        // After the last row, do not expect EOLN (since readLine already consumes it)
        // Only after the last test case, expect EOF
    }

    inf.readEof();
}
