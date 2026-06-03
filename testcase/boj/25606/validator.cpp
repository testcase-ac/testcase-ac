#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 10000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "a");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        inf.readInt(1, n, "t");
        inf.readEoln();
    }

    inf.readEof();
}
