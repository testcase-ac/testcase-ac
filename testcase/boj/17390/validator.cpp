#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000, "A_i");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        int r = inf.readInt(l, n, "R");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
