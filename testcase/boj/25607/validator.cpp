#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, 15, "K");
    inf.readEoln();

    set<int> columns;
    for (int i = 1; i <= k; ++i) {
        int r = inf.readInt(1, n - 1, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, n, "c_i");
        inf.readEoln();

        ensuref(columns.insert(c).second,
                "asteroid columns must be distinct, duplicate column %d at asteroid %d",
                c, i);
    }

    inf.readInt(1, n, "C");
    inf.readEoln();
    inf.readEof();
}
