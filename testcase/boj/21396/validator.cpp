#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readSpace();
        int x = inf.readInt(0, 2000000000, "x");
        inf.readEoln();

        vector<int> v = inf.readInts(n, 0, 2000000000, "v_i");
        inf.readEoln();
    }

    inf.readEof();
}
