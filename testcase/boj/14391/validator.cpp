#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 4, "N");
    inf.readSpace();
    int m = inf.readInt(1, 4, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[0-9]{1,4}", "row");
        inf.readEoln();
        ensuref(int(row.size()) == m, "row %d length is %d, expected %d", i + 1, int(row.size()), m);
    }

    inf.readEof();
    return 0;
}
