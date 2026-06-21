#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 128, "n");
    inf.readSpace();
    int m = inf.readInt(1, 128, "m");
    inf.readEoln();

    // CHECK: BOJ 1998 uses the Korean single-instance format; the English
    // original describes repeated instances ending with 0 0.
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[01]{1,128}", "row");
        ensuref((int)row.size() == m,
                "row %d length is %d, expected %d",
                i + 1,
                (int)row.size(),
                m);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
