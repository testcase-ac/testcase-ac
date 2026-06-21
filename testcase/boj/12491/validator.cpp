#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int case_idx = 1; case_idx <= t; ++case_idx) {
        setTestCase(case_idx);

        int r = inf.readInt(1, 6, "R");
        inf.readSpace();
        int c = inf.readInt(1, 6, "C");
        inf.readEoln();

        for (int i = 0; i < r; ++i) {
            string row = inf.readToken("[#.]{1,6}", "row");
            ensuref((int)row.size() == c,
                    "row %d length is %d, expected %d",
                    i + 1,
                    (int)row.size(),
                    c);
            inf.readEoln();
        }
    }

    inf.readEof();
}
