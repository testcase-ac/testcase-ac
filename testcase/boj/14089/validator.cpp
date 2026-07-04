#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int p = inf.readInt(1, n, "p");
        inf.readSpace();
        int newP = inf.readInt(1, 1000000000, "A");
        inf.readSpace();
        int q = inf.readInt(1, n, "q");
        inf.readSpace();
        int newQ = inf.readInt(1, 1000000000, "B");
        inf.readEoln();

        ensuref(p != q, "query %d has equal positions p=q=%d", i, p);

        a[p - 1] = newP;
        a[q - 1] = newQ;
    }

    inf.readEof();
}
