#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 200, "R");
        inf.readSpace();
        int c = inf.readInt(1, 200, "C");
        inf.readEoln();

        for (int i = 1; i <= r; ++i) {
            string row = inf.readToken("[#*]{1,200}", "row");
            inf.readEoln();

            ensuref((int)row.size() == c,
                    "case %d row %d has length %d, expected %d",
                    tc, i, (int)row.size(), c);
            if (i == 1) {
                ensuref(row[0] == '*',
                        "case %d first grid character must be '*'", tc);
            }
        }
    }

    inf.readEof();
    return 0;
}
