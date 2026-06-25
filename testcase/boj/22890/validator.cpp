#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "N");
        inf.readEoln();

        vector<int> x = inf.readInts(n, 1, 1000000000, "X_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
