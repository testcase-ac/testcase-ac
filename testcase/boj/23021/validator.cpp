#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 5, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 18, "n");
        inf.readSpace();
        int m = inf.readInt(1, 18, "m");
        inf.readSpace();
        int x = inf.readInt(1, 100000000, "x");
        inf.readSpace();
        int c = inf.readInt(1, 1000000000, "C");
        inf.readSpace();
        int d = inf.readInt(c, 1000000000, "D");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 1, 100000000, "A_i");
        inf.readEoln();

        vector<int> b = inf.readInts(m, 1, 100000000, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
