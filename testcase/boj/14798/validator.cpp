#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 25, "R");
        inf.readSpace();
        int c = inf.readInt(1, 25, "C");
        inf.readEoln();

        set<char> seen;
        for (int i = 0; i < r; ++i) {
            string row = inf.readToken("[A-Z?]{1,25}", "row");
            inf.readEoln();

            ensuref((int)row.size() == c,
                    "row %d has length %d, expected %d",
                    i + 1,
                    (int)row.size(),
                    c);

            for (char ch : row) {
                if (ch == '?') {
                    continue;
                }
                ensuref(seen.insert(ch).second,
                        "letter %c appears more than once",
                        ch);
            }
        }

        ensuref(!seen.empty(), "test case must contain at least one letter");
    }

    inf.readEof();
}
