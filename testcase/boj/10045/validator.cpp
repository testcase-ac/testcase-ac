#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        string row = inf.readToken("[JOI]{2,1000}", "flag_row");
        ensuref((int)row.size() == n,
                "flag row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);
        inf.readEoln();
    }

    for (int i = 0; i < 2; ++i) {
        inf.readToken("[JOI]{2}", "emblem_row");
        inf.readEoln();
    }

    inf.readEof();
}
