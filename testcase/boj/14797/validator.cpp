#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int R = inf.readInt(1, 12, "R");
        inf.readSpace();
        int C = inf.readInt(1, 12, "C");
        inf.readEoln();
        ensuref(R * C <= 12, "case %d has R*C=%d, expected at most 12", tc, R * C);

        vector<bool> seen(26, false);
        int letterCount = 0;
        for (int r = 1; r <= R; ++r) {
            string row = inf.readToken("[A-Z?]{1,12}", "row");
            inf.readEoln();
            ensuref((int)row.size() == C,
                    "case %d row %d has length %d, expected %d",
                    tc,
                    r,
                    (int)row.size(),
                    C);

            for (int c = 1; c <= C; ++c) {
                char ch = row[c - 1];
                if ('A' <= ch && ch <= 'Z') {
                    int letter = ch - 'A';
                    ensuref(!seen[letter],
                            "case %d repeats letter %c at row %d column %d",
                            tc,
                            ch,
                            r,
                            c);
                    seen[letter] = true;
                    ++letterCount;
                }
            }
        }

        ensuref(letterCount >= 1, "case %d has no initial letter", tc);
    }

    inf.readEof();
    return 0;
}
