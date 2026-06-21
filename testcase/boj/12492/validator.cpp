#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 50, "R");
        inf.readSpace();
        int c = inf.readInt(1, 50, "C");
        inf.readEoln();

        for (int i = 0; i < r; ++i) {
            string row = inf.readLine("[#.]{1,50}", "row");
            ensuref((int)row.size() == c,
                    "row %d has length %d, expected %d",
                    i + 1,
                    (int)row.size(),
                    c);
        }
    }

    inf.readEof();
}
