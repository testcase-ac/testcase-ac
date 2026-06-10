#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of scenarios.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 10, "m");
        inf.readEoln();

        vector<int> n = inf.readInts(m, 1, 10000, "n_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
