#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "N");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 1, n, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
